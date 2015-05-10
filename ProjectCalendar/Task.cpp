#include "Task.h"

template <class T,class F>
TasksContainer TaskFactory<T,F>::tasks = 0;

CompositeFactory::Handler CompositeFactory::handler = CompositeFactory::Handler();
PreemptiveFactory::Handler PreemptiveFactory::handler = PreemptiveFactory::Handler();
NonPreemptiveFactory::Handler NonPreemptiveFactory::handler = NonPreemptiveFactory::Handler();

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
    for (CompositeFactory::TasksIterator it = cf->getIterator(*this); !(it.isDone()); it.next()) {
        cf->removeTask(&(it.current()));
    }
    cf->removeTask(this);
}

bool CompositeTask::isSubTaskHere(const QString &id) const {
    for (CompositeFactory::TasksIterator it = CompositeFactory::getInstance().getIterator(*this); !(it.isDone()); it.next()) {
        if (it.current().getId() == id) return true;
    }
    return false;
}

void CompositeTask::addSubTask(Task &t) {
    if (isSubTaskHere(t.getId())) throw CalendarException("Error : sub-task "+t.getId()+" has already been added in "+getId());
    subTasks.push_back(&t);
}


Task& CompositeTask::getSubTask(const QString &id) {
    for (CompositeFactory::TasksIterator it = CompositeFactory::getInstance().getIterator(*this); !(it.isDone()); it.next()) {
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






