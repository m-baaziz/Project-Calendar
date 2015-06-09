#include "Project.h"
#include "TaskManager.h"
#include "Association.h"

template<>
Handler<ProjectFactory> Singleton<ProjectFactory>::handler = Handler<ProjectFactory>();


bool Project::isTaskAdded(Task *t) {
    for (typename TasksContainer::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        if (*it == t || ((*it)->getTaskType()==COMPOSITE && dynamic_cast<CompositeTask*>(*it)->isSubTaskHere(t->getId()))) return true;
    }
    return false;
}

bool Project::isTaskValidForProject(Task &t) {
    CompositeTask* includer;
    if (!(ProjectFactory::getInstance().isTaskavalaible(&t))) throw CalendarException("Error : Task "+t.getId()+" has already been added to a project ");
    if (includer = CompositeFactory::getInstance().isTaskIncluded(t.getId()))
        throw CalendarException("Error : you can't add to a project a task that is included in a composite Task, pleas add instead the composite Task ("+includer->getId()+")");
    if (t.getDisponibility()<this->getDisponibility() || t.getDeadline()>this->getDeadline())
        throw CalendarException("Error : Task "+t.getId()+" can't be added in Project "+this->getId()+" because the task's disponibility/deadline is not compatible with the project disponibility/deadline");
    return true;
}

Task& Project::addTask(Task &t) {
    CompositeTask* includer;
    if (!(ProjectFactory::getInstance().isTaskavalaible(&t))) throw CalendarException("Error : Task "+t.getId()+" has already been added to a project ");
    if (includer = CompositeFactory::getInstance().isTaskIncluded(t.getId()))
        throw CalendarException("Error : you can't add to a project a task that is included in a composite Task, pleas add instead the composite Task ("+includer->getId()+")");
    if (t.getDisponibility()<this->getDisponibility() || t.getDeadline()>this->getDeadline())
        throw CalendarException("Error : Task "+t.getId()+" can't be added in Project "+this->getId()+" because the task's disponibility/deadline is not compatible with the project disponibility/deadline");
    TasksContainer predecessors = AssociationManager::getInstance().getTaskPredecessors(&t);
    for (TasksContainer::iterator it = predecessors.begin(); it!=predecessors.end(); ++it) {
        if (!(isTaskAdded(*it)) && !(t.getTaskType()==COMPOSITE && dynamic_cast<CompositeTask&>(t).isSubTaskHere((*it)->getId()))) throw CalendarException("Error : task "+t.getId()+" has to follow "+(*it)->getId()+" , pleas add "+(*it)->getId()+" to the Project");
    }
    durationBuffer = durationBuffer+t.getDuration();
    if (durationBuffer>getDuration()) setDuration(durationBuffer);
    tasks.push_back(&t);
    return t;
}

void Project::removeTask(const QString &id) {
    for (TasksContainer::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        if ((*it)->getId() == id) {
            Task* toDelete = *it;
            tasks.erase(it);
            NonPreemptiveFactory::getInstance().removeTask(toDelete);
            return;
        }
    }

}

void Project::softRemoveTask(const QString &id) {
    for (TasksContainer::iterator it = tasks.begin(); it != tasks.end(); ++it) {
        if ((*it)->getId() == id) {
            tasks.erase(it);
            return;
        }
    }
}

Project::~Project() {
    while(!(tasks.empty())) removeTask(tasks.front()->getId());
    tasks.clear();
}


TasksContainer Project::getRootTasks() {
    TasksContainer temp;
    bool isHere = false;  // to test if a task has already been added into the buffer.
    AssociationManager::AssociationRootTasksIterationStrategy strat;
    AssociationManager::NotAssociationRootTasksIterationStrategy strat1;
    for (Iterator<Task> it = getIterator(&strat); !(it.isDone()); it.next())
        temp.push_back(&(it.current()));
    for (Iterator<CompositeTask> it = getIterator<CompositeTask>(&strat1); !(it.isDone()); it.next())
        it.current().getAssociationRootTasks(&temp);
    TasksContainer toSend = TasksContainer();
    for (TasksContainer::iterator it2 = temp.begin(); it2!=temp.end(); ++it2) { // we remove duplicates
        for (TasksContainer::iterator it = toSend.begin(); it!=toSend.end(); ++it) {
            if (*it2==*it) isHere = true;
            break;
        }
        if (!isHere) toSend.push_back(*it2);
    }
    return toSend;
}

////////////////////////////////////////////////////////////////////

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
    Project* toSend = findProject(id);
    if (toSend == 0) throw CalendarException("Error : Project "+id+" not found !");
    return *toSend;
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
            Project* toDelete = *itp;
            projects.erase(itp);
            delete toDelete;
            return;
        }
    }
}

ProjectFactory::~ProjectFactory() {
    while(!(projects.empty())) removeProject(projects.front());
    projects.clear();
}

Project* ProjectFactory::getTaskProject(Task *t) {
    for (ProjectsContainer::iterator it = projects.begin(); it!=projects.end(); ++it) {
        if ((*it)->isTaskAdded(t)) return *it;
    }
    return 0;
}
