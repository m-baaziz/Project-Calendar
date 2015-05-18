#ifndef ASSOCIATION_H
#define ASSOCIATION_H
#include "Task.h"

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
    ~Association(){}
};

class AssociationManager: public Singleton<AssociationManager> {
    AssociationManager(){}
    AssociationManager(const AssociationManager& a);
    AssociationManager& operator=(const AssociationManager& a);
    ~AssociationManager(){}

    friend class Singleton<AssociationManager>;
    friend class Handler<AssociationManager>;
};

#endif // ASSOCIATION_H
