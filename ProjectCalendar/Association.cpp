#include "Association.h"
#include "Task.h"

template<>
Handler<AssociationManager> Singleton<AssociationManager>::handler = Handler<AssociationManager>();

// ASSOCIATION



// ASSOCIATION MANAGER

void AssociationManager::fillQueue(std::queue<Task*>& q, TasksContainer tc) {
    for (TasksContainer::iterator it = tc.begin(); it!=tc.end(); ++it)
        q.push(*it);
}

bool AssociationManager::isTaskXFollowedByY(Task* X,Task* Y) {
    std::queue<Task*> taskQueue;
    fillQueue(taskQueue,AssociationManager::getInstance().getTaskSuccessors(X));
    Task* son;
    while (!(taskQueue.empty())) {
        son = taskQueue.front();
        taskQueue.pop();
        if (son == Y) return true;
        fillQueue(taskQueue,AssociationManager::getInstance().getTaskSuccessors(son));
    }
    return false;
}

void AssociationManager::removeTaskAssociationLinks(Task* t) {
    for (AssociationsContainer::iterator it = assos.begin(); it!=assos.end();) {
        if ((*it)->getPredecessor()==t || (*it)->getSuccessor()==t) {
            delete *it;
            assos.erase(it);
        }
        else ++it;
    }
}

Association& AssociationManager::addAssociation(Task* p, Task* s) {
    if (p == s) throw CalendarException("Error : a Task can't succeed or precede itself");
    if (isTaskXFollowedByY(s,p)) throw CalendarException("Error : "+p->getId()+" can't preceed "+s->getId()+" because "+s->getId()+" is already followed by "+p->getId());
    if (isTaskXFollowedByY(p,s)) throw CalendarException("Error : "+s->getId()+" has already been added as a successor of "+p->getId());
    if (s->getTaskType()==COMPOSITE && dynamic_cast<CompositeTask*>(s)->isSubTaskHere(p->getId())) throw CalendarException("a sub-task can't preceed its composite task");
    QDate temp = p->getDisponibility();
    temp.addDays(p->getDuration().getDurationInHours()/24);
    if (temp > s->getDeadline()) throw CalendarException("Error : "+p->getId()+" can't preceed "+s->getId()+" because it can't be realized before its successor's deadline");
    Association* toAdd = new Association(p,s);
    assos.push_back(toAdd);
    return *toAdd;
}

void AssociationManager::removeAssociation(Task* p, Task* s) {
    for (AssociationsContainer::iterator it = assos.begin(); it!=assos.end(); ++it) {
        if ((*it)->getPredecessor()==p && (*it)->getSuccessor()==s) {
            delete *it;
            assos.erase(it);
            return;
        }
    }
}

TasksContainer AssociationManager::getTaskPredecessors(Task* t) {
    TasksContainer toSend;
    for (AssociationsContainer::iterator it = assos.begin(); it!=assos.end(); ++it) {
        if ((*it)->getSuccessor()==t && (*it)->getPredecessor()) toSend.push_back((*it)->getPredecessor());
    }
    return toSend;
}

TasksContainer AssociationManager::getTaskSuccessors(Task* t) {
    TasksContainer toSend;
    for (AssociationsContainer::iterator it = assos.begin(); it!=assos.end(); ++it) {
        if ((*it)->getPredecessor()==t && (*it)->getSuccessor()) toSend.push_back((*it)->getSuccessor());
    }
    return toSend;
}

