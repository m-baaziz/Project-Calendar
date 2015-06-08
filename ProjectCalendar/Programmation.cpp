#include "Programmation.h"

template<>
Handler<ProgrammationFactory> Singleton<ProgrammationFactory>::handler = Handler<ProgrammationFactory>();

bool ProgrammationFactory::isScheduled(UnitaryTask *t) {
    for (EventsContainer::iterator it =events.begin(); it!=events.end(); ++it) {
        if ((*it)->task == t && !(t->isPreemptive())) return true;
        if ((*it)->task == t && t->isPreemptive() &&
                getTimeLeftToSchedule(dynamic_cast<PreemptiveTask*>(t)).getDurationInMinutes()==0)
            return true;
    }
    return false;
}

Programmation& ProgrammationFactory::scheduleTask(UnitaryTask *t, const QString &n, const QDate &d, const QTime &ti, const Duration &du, const QString &p, const QDate &da, const ParticipantsContainer &par) {
    if (isScheduled(t)) throw CalendarException("Error : Task "+t->getId()+" already scheduled");
    if (d<t->getDisponibility()) throw CalendarException("Error : a Task can't be scheduled before its disponibility date");
    if (QDate(d.year(),d.month(),d.day()+(ti.hour()+du.getDurationInHours())/24)>t->getDeadline()) throw CalendarException("Error : a Task can't be scheduled after its deadline");
    if (du.getDurationInHours()>12) throw CalendarException("Error : a single programmation can't last for more than 12 hours");
    if (!(getTaskToSchedule(t).empty())) throw CalendarException("Error : Pleas respect precedence constraints, you need to schedule "+t->getId()+"'s predecessors before beeing able to schedule it");
    if (!isTimeZoneFree(d,ti,du)) throw CalendarException("Error : Time zone not available");
    if (t->isPreemptive()) {
           // treatment on the preemptive task
        PreemptiveTask* target = dynamic_cast<PreemptiveTask*>(t);
        Duration timeLeft = getTimeLeftToSchedule(target);
        if (timeLeft<du) throw CalendarException("Error : time left (to be scheduled) for task "+t->getId()+" : "+timeLeft.toString());
    }
    else {
        // treatment on the non preemptive task
    }
    Programmation* toAdd = new Programmation(n,d,ti,p,da,du,t,par);   //make the programmation
    events.push_back(toAdd);   // add it
}

Duration ProgrammationFactory::getTimeLeftToSchedule(PreemptiveTask *t) {
    unsigned int minutes = 0;
    Programmation* temp;
    EventsContainer taskProgs = getProgrammations(t);
    if (taskProgs.empty()) return t->getDuration();
    while(!(taskProgs.empty())) {
        temp = taskProgs.back();
        minutes += temp->getDuration().getDurationInMinutes();
    }
    minutes = t->getDuration().getDurationInMinutes() - minutes;
    return minutes;
}

Programmation* ProgrammationFactory::getProgrammation(NonPreemptiveTask *t) {
    for (EventsContainer::iterator it = events.begin(); it!=events.end(); ++it)
        if ((*it)->getTask()==t) return *it;
    return 0;
}

Programmation* ProgrammationFactory::getProgrammation(PreemptiveTask *t, const QDate &d, const QTime &ti) {
    for (EventsContainer::iterator it = events.begin(); it!=events.end(); ++it)
        if ((*it)->getTask()==t && (*it)->getDate()==d && (*it)->getTime()==ti) return *it;
    return 0;
}

ProgrammationFactory::EventsContainer ProgrammationFactory::getProgrammations(PreemptiveTask *t) {
    EventsContainer buffer = EventsContainer();
    for (EventsContainer::iterator it = events.begin(); it!=events.end(); ++it)
        if ((*it)->getTask() == t) buffer.push_back(*it);
    return buffer;
}

ProgrammationFactory::EventsContainer ProgrammationFactory::getProgrammations(PreemptiveTask *t, const QDate &d) {
    EventsContainer buffer = EventsContainer();
    for (EventsContainer::iterator it = events.begin(); it!=events.end(); ++it)
        if ((*it)->getTask() == t && (*it)->getDate()==d) buffer.push_back(*it);
    return buffer;
}

TasksContainer ProgrammationFactory::getTaskToSchedule(UnitaryTask *t) {
    TasksContainer predecessors = AssociationManager::getInstance().getTaskPredecessors(t);
    Task* temp=0;
    for (TasksContainer::iterator it = predecessors.begin(); it!=predecessors.end(); ++it) {
        temp = (*it);
        if (temp->getTaskType()==UNITARY && !(isScheduled(dynamic_cast<UnitaryTask*>(temp))))
            predecessors.push_back(temp);
    }
    return predecessors;
}
