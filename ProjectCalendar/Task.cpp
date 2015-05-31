#include "Task.h"
#include "TaskManager.h"


// PREEMPTIVE TASK

PreemptiveTask::~PreemptiveTask() {}

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
    if (t.getDisponibility()<this->getDisponibility() || t.getDeadline()>this->getDeadline())
        throw CalendarException("Error : Task "+t.getId()+" can't be included in "+this->getId()+" because the subtask disponibility/deadline is not compatible with parent task");
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


