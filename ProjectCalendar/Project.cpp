#include "Project.h"

template<>
Handler<ProjectFactory> Singleton<ProjectFactory>::handler = Handler<ProjectFactory>();


bool Project::isTaskAdded(Task *t) {
    for (typename TasksContainer::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        if (*it == t) return true;
        if ((*it)->getTaskType()==COMPOSITE && dynamic_cast<CompositeTask*>(*it)->isSubTaskHere(t->getId())) return true;
    }
    return false;
}

Task& Project::addTask(Task &t) {
    if (isTaskAdded(&t)) throw CalendarException("Error : Task "+t.getId()+" has already been added to the project "+getId());
    tasks.push_back(&t);
    return t;
}

void Project::removeTask(const QString &id) {
    for (TasksContainer::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        if ((*it)->getId() == id) tasks.erase(it);
    }
}
