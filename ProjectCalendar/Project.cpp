#include "Project.h"
#include "TaskManager.h"

template<>
Handler<ProjectFactory> Singleton<ProjectFactory>::handler = Handler<ProjectFactory>();


bool Project::isTaskAdded(Task *t) {
    for (typename TasksContainer::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        if (*it == t) return true;
    }
    return false;
}

Task& Project::addTask(Task &t) {
    CompositeTask* includer;
    if (!(ProjectFactory::getInstance().isTaskavalaible(&t))) throw CalendarException("Error : Task "+t.getId()+" has already been added to a project ");
    if (includer = CompositeFactory::getInstance().isTaskIncluded(t.getId()))
        throw CalendarException("Error : you can't add to a project a task that is included in a composite Task, pleas add instead the composite Task ("+includer->getId()+")");
    if (t.getDisponibility()<this->getDisponibility() || t.getDeadline()>this->getDeadline())
        throw CalendarException("Error : Task "+t.getId()+" can't be added in Project "+this->getId()+" because the task's disponibility/deadline is not compatible with the project disponibility/deadline");
    tasks.push_back(&t);
    return t;
}

void Project::removeTask(const QString &id) {
    for (TasksContainer::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        if ((*it)->getId() == id) {
            tasks.erase(it);
            return;
        }
    }
}

bool ProjectFactory::isTaskavalaible(Task* t) {
    for (ProjectsContainer::iterator it = projects.begin(); it!=projects.end(); ++it) {
        if ((*it)->isTaskAdded(t)) return false;
    }
    return true;
}

Project* ProjectFactory::findProject(const QString& id) {
    for (ProjectsContainer::iterator it = projects.begin(); it!=projects.end(); ++it)
        if ((*it)->getId() == id) return *it;
    return 0;
}

bool ProjectFactory::isProjectHere(const QString& id) {
    return findProject(id) != 0;
}

bool ProjectFactory::isProjectHere(const Project* const p) {
    for (ProjectsContainer::iterator it = projects.begin(); it!=projects.end(); ++it)
        if (*it == p) return true;
    return false;
}

Project& ProjectFactory::getProject(const QString &id) {
    return *(findProject(id));
}

Project& ProjectFactory::addProject(const QString &id, const QString &t, const Duration &dur, const QDate &dispo, const QDate &term) {
    if (isProjectHere(id)) throw CalendarException("Error : Project "+id+"has already been added");
    Project* toAdd = new Project(id,t,dur,dispo,term);
    projects.push_back(toAdd);
    return *toAdd;
}

void ProjectFactory::removeProject(Project* p) {
    for (ProjectsContainer::iterator itp = projects.begin(); itp!= projects.end(); ++itp) {
        if (p && *itp == p) {
            p->clearArray();
            delete *itp;
            projects.erase(itp);
            return;
        }
    }
}

ProjectFactory::~ProjectFactory() {
    while(!(projects.empty())) removeProject(projects.front());
    projects.clear();
}


