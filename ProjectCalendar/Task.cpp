#include "Task.h"

template <class T,class F>
TasksContainer TaskFactory<T,F>::tasks = TasksContainer();

template<>
TaskFactory<CompositeTask,CompositeFactory>::Handler<CompositeTask,CompositeFactory> TaskFactory<CompositeTask,CompositeFactory>::handler = TaskFactory::Handler<CompositeTask,CompositeFactory>();
template<>
TaskFactory<PreemptiveTask,PreemptiveFactory>::Handler<PreemptiveTask,PreemptiveFactory> TaskFactory<PreemptiveTask,PreemptiveFactory>::handler = TaskFactory::Handler<PreemptiveTask,PreemptiveFactory>();
template<>
TaskFactory<NonPreemptiveTask,NonPreemptiveFactory>::Handler<NonPreemptiveTask,NonPreemptiveFactory> TaskFactory<NonPreemptiveTask,NonPreemptiveFactory>::handler = TaskFactory::Handler<NonPreemptiveTask,NonPreemptiveFactory>();

// PREEMPTIVE TASK

PreemptiveTask::~PreemptiveTask() {
    PreemptiveFactory::getInstance().removeTask(this);
}

void PreemptiveTask::setInterruption() {
    // to do : manage interruptions
}

// NONPREEMPTIVE TASK

NonPreemptiveTask::~NonPreemptiveTask() {
    NonPreemptiveFactory::getInstance().removeTask(this);
}

// COMPOSITE TASK

CompositeTask::~CompositeTask() {
    CompositeFactory* cf = &(CompositeFactory::getInstance());
    for (CompositeFactory::TasksIterator it = cf->getIterator(this); !(it.isDone()); it.next()) {
        cf->removeTask(&(it.current()));
    }
    cf->removeTask(this);
}

bool CompositeTask::isSubTaskHere(const QString &id) const {
    for (CompositeFactory::TasksIterator it = CompositeFactory::getInstance().getIterator(this); !(it.isDone()); it.next()) {
        if (it.current().getId() == id) return true;
    }
    return false;
}

void CompositeTask::addSubTask(Task &t) {
    if (isSubTaskHere(t.getId())) throw CalendarException("Error : sub-task "+t.getId()+" has already been added in "+getId());
    subTasks.push_back(&t);
}


Task& CompositeTask::getSubTask(const QString &id) {
    for (CompositeFactory::TasksIterator it = CompositeFactory::getInstance().getIterator(this); !(it.isDone()); it.next()) {
        if (it.current().getId() == id) return it.current();
    }
    throw CalendarException("Error : sub-task "+id+" not found in "+getId());
}

void CompositeTask::removeSubTask(const QString &id) {
    for (TasksContainer::iterator it = subTasks.begin(); it!=subTasks.end(); ++it) {
        if ((*it)->getId()==id) {
            CompositeFactory::getInstance().removeTask(*it);
            subTasks.erase(it);
            return;
        }
    }
    throw CalendarException("Error : sub-task "+id+" not found in "+getId());
}

// TASK FACTORY

template <class T,class F>
void TaskFactory<T,F>::addItem(Task* t) {
    tasks.push_back(t);
}

template <class T,class F>
TaskFactory<T,F>::~TaskFactory() {
    //if (file!="") this->save(file);
    for (TasksContainer::iterator it = tasks.begin(); it!=tasks.end(); ++it) {
        delete *it;
    }
    tasks.clear();
    delete &tasks;
    file="";
}

template <class T,class F>
void TaskFactory<T,F>::freeInstance() {
    if (handler.instance!=0) delete handler.instance;
    handler.instance = 0;
}

template <class T,class F>
void TaskFactory<T,F>::removeTask(Task *t) {
    for (TasksContainer::iterator it = tasks.begin(); it!=tasks.end(); ++it) {
        if (*it==t) {
            delete *it;
            tasks.erase(it);
            return;
        }
    }
}

template <class T,class F>
void TaskFactory<T,F>::TasksIterator::next() {
    if (isDone()) throw CalendarException("Error : next on a finished iterator");
    currentTask.pop_back();
}

template <class T,class F>
void TaskFactory<T,F>::TypedTasksIterator::next(){
    if (this->isDone()) throw CalendarException("Error, indirection on a finished iterator");
    while (this->currentTask.back().getTaskType()!=specificTaskType()) {
        this->currentTask.pop_back();
    }
}

// UNITARY TASK FACTORY

template<class T2,class F2>
void UnitaryFactory<T2,F2>::SubTypedTasksIterator::next() {
    if (this->isDone()) throw CalendarException("Error : next on a finished iterator");
    while (!(*(this->currentTask[this->currentTask.size()])->getTaskType()==UNITARY && dynamic_cast<UnitaryTask*>(*(this->currentTask[this->currentTask.size()]))->getUnitarySubType()==specificTaskSubType())) {
    this->currentTask.pop_back(); //Dynamic cast possible because of the first condition
    }
}

