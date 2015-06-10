#ifndef ASSOCIATION_H
#define ASSOCIATION_H
#include "Task.h"
#include "Calendar.h"
#include "Singleton.h"
#include "Iterator.h"

/*!
 *\file Association.h
 *\brief Header file that describes the classes related with predecessor and successor relations betweeen tasks.
 */

class Association {
    Task* predecessor;
    Task* successor;

    Association():predecessor(0),successor(0){}
    Association(Task* p, Task* s): predecessor(p),successor(s){}
    Association& operator=(const Association& a);
    ~Association(){
        if (successor->getTaskType()==COMPOSITE) {
            CompositeTask* temp = dynamic_cast<CompositeTask*>(successor);
            if (temp->isItemHere(predecessor)) temp->removeSubTask(predecessor->getId());
        }
    }

    friend class AssociationManager;
public:
    Task* getPredecessor() const {return predecessor;}
    Task* getSuccessor() const {return successor;}
};

typedef Iterator<Association> AssociationIterator;
typedef std::vector<Association*> AssociationsContainer;

class AssociationManager: public Singleton<AssociationManager>, public Aggregator<Association> {
    AssociationsContainer assos;

    AssociationManager():Aggregator<Association>(&assos){}
    AssociationManager(const AssociationManager& a);
    AssociationManager& operator=(const AssociationManager& a);
    ~AssociationManager(){}
    void fillQueue(std::queue<Task*>& q, TasksContainer tc);
    bool isTaskXFollowedByY(Task* X,Task* Y);
    void removeTaskAssociationLinks(Task* t);

    friend class Singleton<AssociationManager>;
    friend class Handler<AssociationManager>;
    template<class anytask,class anyfactory>
    friend class TaskFactory; // friendship to allow taskFactory to call removeTaskAssociationLinks when removing a task.

public:
    Association& addAssociation(Task* p, Task* s);  // many verifications to do
    void removeAssociation(Task* p, Task* s);
    TasksContainer getTaskPredecessors(Task* t);
    TasksContainer getTaskSuccessors(Task* t);

    class AssociationRootTasksIterationStrategy : public TasksIterationStrategy {
        bool test(Task *tested) const override {
            return getInstance().getTaskPredecessors(tested).empty();
        }
    };
    class NotAssociationRootTasksIterationStrategy : public TasksIterationStrategy {
        bool test(Task *tested) const override {
            return !(getInstance().getTaskPredecessors(tested).empty());
        }
    };
};

#endif // ASSOCIATION_H
