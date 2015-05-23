#include "Task.h"

TasksContainer* TasksArray::tasks = new TasksContainer;
unsigned int TasksArray::nbFactories = 0;

template<>
Handler<CompositeFactory> Singleton<CompositeFactory>::handler = Handler<CompositeFactory>();
template<>
Handler<PreemptiveFactory> Singleton<PreemptiveFactory>::handler = Handler<PreemptiveFactory>();
template<>
Handler<NonPreemptiveFactory> Singleton<NonPreemptiveFactory>::handler = Handler<NonPreemptiveFactory>();

// TASK

void Task::checkCompositionValidity() {
    CompositeFactory* cf = &(CompositeFactory::getInstance());
    CompositeTask* includer;
    for (CompositeFactory::TypedTasksIterator it = cf->getTypedTasksIterator(); !(it.isDone()); it.next()) {
        includer = &(it.current()); // here we can't use the TypedTasksIterator to get only composite Tasks because it will use a redefined pure virtual method, which may cause some trouble if this method is called during CompositeFactory destruction.
        //if (!includer) continue;  // includer=0 when we get this deleted task.
        includer = includer->isSubTaskHere(this->getId());
        if (includer) {
            includer->removeSubTask(this->getId());
            return;
        }
    }
}

// PREEMPTIVE TASK

PreemptiveTask::~PreemptiveTask() {}

void PreemptiveTask::setInterruption() {
    // to do : manage interruptions
}

// NONPREEMPTIVE TASK

NonPreemptiveTask::~NonPreemptiveTask() {}

// COMPOSITE TASK

CompositeTask::~CompositeTask() {
    CompositeFactory* cf = &(CompositeFactory::getInstance());
    while(!(subTasks.empty())) cf->removeTask(subTasks.front());
    subTasks.clear();
}

void CompositeTask::fillQueue(std::queue<SubTaskCouple>& qu,const TasksContainer& st,CompositeTask* includer) const {
    for (TasksContainer::const_iterator it = st.begin(); it!=st.end(); ++it) {
        qu.push(SubTaskCouple(*it,includer));
    }
}

CompositeTask* CompositeTask::isSubTaskHere(const QString &id) {
    std::queue<SubTaskCouple> tasksQueue;
    SubTaskCouple test;
    this->fillQueue(tasksQueue,subTasks,this);
    while(!(tasksQueue.empty())) {
        test.included = tasksQueue.front().included;
        test.includer = tasksQueue.front().includer;
        tasksQueue.pop();
        if (test.included->getId()==id) {
            return test.includer;
        }
        if (test.included->getTaskType()==COMPOSITE) this->fillQueue(tasksQueue,(dynamic_cast<CompositeTask*>(test.included))->getSubTasksArray(),(dynamic_cast<CompositeTask*>(test.included)));
    }
    return 0;
}

void CompositeTask::addSubTask(Task &t) {
    CompositeTask* temp = 0;
    if (subTasks.empty() && t.getTaskType()==COMPOSITE && dynamic_cast<CompositeTask*>(&t)->getSubTasksArray().empty())
        throw CalendarException("Error : a composite Task can't include only composite tasks");
    if (temp = CompositeFactory::getInstance().isTaskIncluded(t.getId()))
        throw CalendarException("Error : sub-task "+t.getId()+" has already been added in "+temp->getId());
    if ((t.getTaskType()==COMPOSITE &&dynamic_cast<CompositeTask*>(&t)->isSubTaskHere(this->getId()))) // This huge condition checks if this task includes "t" or if "t" is a composite task that includes this task.
        throw CalendarException("Error : The task "+t.getId()+" already includes the task "+this->getId());
    subTasks.push_back(&t);  // check if there is an unitary task at the end, and if this "this" is not included in the task's arborescence
}


Task& CompositeTask::getSubTask(const QString &id) {
    for (TasksIterator it = this->getIterator(); !(it.isDone()); it.next()) {
        if (it.current().getId() == id) return it.current();
    }
    throw CalendarException("Error : sub-task "+id+" not found in "+getId());
}

void CompositeTask::removeSubTask(const QString &id) {
    for (TasksContainer::iterator it = subTasks.begin(); it!=subTasks.end(); ++it) {
        if ((*it)->getId()==id) {
            subTasks.erase(it);
            return;
        }
    }
    throw CalendarException("Error : sub-task "+id+" not found in "+getId());
}

// COMPOSITE FACTORY

CompositeTask* CompositeFactory::isTaskIncluded (const QString& id) {
    CompositeTask* temp = 0;
    for (TypedTasksIterator it = getTypedTasksIterator(); !(it.isDone()); it.next()) {
        if (temp = it.current().isSubTaskHere(id)) return temp;
    }
    return 0;
}

