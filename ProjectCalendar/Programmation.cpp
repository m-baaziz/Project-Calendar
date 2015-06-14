#include "Programmation.h"
#include "TaskManager.h"

template<>
Handler<ProgrammationFactory> Singleton<ProgrammationFactory>::handler = Handler<ProgrammationFactory>();

bool ProgrammationFactory::isScheduled(UnitaryTask *t) {
    for (Iterator<Programmation> it = getIterator<Programmation>(); !(it.isDone()); it.next()) {
        if (it.current().getTask() == t && !(t->isPreemptive())) return true;
        if (it.current().getTask() == t && t->isPreemptive() &&
                getTimeLeftToSchedule(dynamic_cast<PreemptiveTask*>(t)).getDurationInMinutes()==0)
            return true;
    }
    return false;
}

Programmation& ProgrammationFactory::scheduleTask(UnitaryTask *t, const QString &n, const QDate &d, const QTime &ti, const Duration &du, const QString &p, const ParticipantsContainer &par) {
    Duration tempDu = du;
    qDebug()<<"AAA";
    if (!(du+ti).isValid()) tempDu = Duration(du.getDurationInMinutes()-1);
    qDebug()<<"BBB";
    if (du>t->getDuration()) throw CalendarException("Error : task "+t->getId()+"'s duration is : "+t->getDuration().toString()+", pleas decrease the duration of your programmation");
    qDebug()<<"CCC";
    if (!(t->isPreemptive()) && du!=t->getDuration()) throw CalendarException("Error : Non preemptive Tasks can't be interrupted, you have to give the full task duration as a programmation duration ("+t->getDuration().toString()+")");
    qDebug()<<"DDD";
    if (n.size()==0 || p.size()==0) throw CalendarException("Error : Invalid parameters");
    qDebug()<<"EEE";
    if (isEventHere(n)) throw CalendarException("Error : a Programmation with the name of "+n+" has already been done");
    qDebug()<<"FFF";
    if (isScheduled(t)) throw CalendarException("Error : Task "+t->getId()+" already scheduled");
    qDebug()<<"GGG";
    if (d<(t->getDisponibility())) throw CalendarException("Error : a Task can't be scheduled before its disponibility date");
    qDebug()<<"HHH";
    if (QDate(d.year(),d.month(),d.day()+(ti.hour()+du.getDurationInHours())/24)>t->getDeadline()) throw CalendarException("Error : a Task can't be scheduled after its deadline");
    qDebug()<<"III";
    if (tempDu+ti<ti) throw CalendarException("Error : a single event can not happen in two different days, pleas schedule two differents events");
    qDebug()<<"JJJ";
    if (du.getDurationInHours()>12) throw CalendarException("Error : a single programmation can't last for more than 12 hours");
    qDebug()<<"KKK";
    TasksContainer toSchedule = getTaskToSchedule(t);
    qDebug()<<"LLL";
    if (!(toSchedule.empty())) throw toSchedule;//throw CalendarException("Error : Pleas respect precedence constraints, you need to schedule "+t->getId()+"'s predecessors before beeing able to schedule it");
    qDebug()<<"MMM";
    if (!isTimeZoneFree(d,ti,du)) throw CalendarException("Error : Time zone not available");
    if (t->isPreemptive()) {
        qDebug()<<"NNN";
        PreemptiveTask* target = dynamic_cast<PreemptiveTask*>(t);
        qDebug()<<"OOO";
        Duration timeLeft = getTimeLeftToSchedule(target);
        qDebug()<<"PPP";
        if (timeLeft<du) throw CalendarException("Error : time left (to be scheduled) for task "+t->getId()+" : "+timeLeft.toString());        
        qDebug()<<"QQQ";
    }
    qDebug()<<"RRR";
    Programmation* toAdd = new Programmation(n,d,ti,p,tempDu,t,par);   //make the programmation
    qDebug()<<"SSS";
    events->push_back(toAdd);
    qDebug()<<"TTT";
    return *toAdd;
}

Duration ProgrammationFactory::getTimeLeftToSchedule(PreemptiveTask *t) {
    unsigned int minutes = 0;
    Programmation* temp;
    qDebug()<<"111";
    SpecificEventsContainer taskProgs = getProgrammations(t);
    qDebug()<<"222";
    if (taskProgs.empty()) return t->getDuration();
    while(!(taskProgs.empty())) {
        temp = taskProgs.back();
        taskProgs.pop_back();
        minutes += temp->getDuration().getDurationInMinutes();
    }
    minutes = t->getDuration().getDurationInMinutes() - minutes;
    return minutes;
}

Programmation* ProgrammationFactory::getProgrammation(NonPreemptiveTask *t) {
    for (Iterator<Programmation> it = getIterator<Programmation>(); !(it.isDone()); it.next())
        if (it.current().getTask()==t) return &it.current();
    return 0;
}

Programmation* ProgrammationFactory::getProgrammation(PreemptiveTask *t, const QDate &d, const QTime &ti) {
    for (Iterator<Programmation> it = getIterator<Programmation>(); !(it.isDone()); it.next())
        if (it.current().getTask()==t && it.current().getDate()==d && it.current().getTime()==ti) return &it.current();
    return 0;
}

EventFactory<Programmation,ProgrammationFactory>::SpecificEventsContainer ProgrammationFactory::getProgrammations(UnitaryTask *t) {
    SpecificEventsContainer buffer = SpecificEventsContainer();
    for (Iterator<Programmation> it = getIterator<Programmation>(); !(it.isDone()); it.next())
        if (it.current().getTask()==t)  buffer.push_back(&it.current());
    return buffer;
}

EventFactory<Programmation,ProgrammationFactory>::SpecificEventsContainer ProgrammationFactory::getProgrammations(UnitaryTask *t, const QDate &d) {
    SpecificEventsContainer buffer = SpecificEventsContainer();
    for (Iterator<Programmation> it = getIterator<Programmation>(); !(it.isDone()); it.next())
        if (it.current().getTask()==t && it.current().getDate()==d) buffer.push_back(&it.current());
    return buffer;
}

TasksContainer ProgrammationFactory::getTaskToSchedule(UnitaryTask *t) {
    TasksContainer predecessors = AssociationManager::getInstance().getTaskPredecessors(t);
    TasksContainer toSend = TasksContainer();
    Task* temp=0;
    for (TasksContainer::iterator it = predecessors.begin(); it!=predecessors.end(); ++it) {
        temp = *it;
        if (temp->getTaskType()==UNITARY && !(isScheduled(dynamic_cast<UnitaryTask*>(temp))))
            toSend.push_back(temp);
    }
    return toSend;
}

void ProgrammationFactory::removeProgrammation(UnitaryTask *t) {
    SpecificEventsContainer toDelete = getProgrammations(t);
    for (Iterator<Programmation> it = getIterator<Programmation>(); !(it.isDone()); it.next())
        removeEvent(it.current().getName());
}

void ProgrammationFactory::removeSpecificProgrammation(UnitaryTask *t, const QDate &d, const QTime &ti) {
  Programmation* toDelete = getSpecificEventByDateAndTime(d,ti);
  if (toDelete->getTask()==t)
      removeEvent(toDelete->getName());
  else throw CalendarException("Error : Programmation not found");
}

void ProgrammationFactory::achieveEvent(const QString &name) {
    Programmation* toAchieve = getSpecificEvent(name);
    UnitaryTask* task = toAchieve->getTask();
    toAchieve->setToAchieved();
    if (!isScheduled(task)) return;
    TasksContainer array = TasksContainer();
    if (!(task->isPreemptive())) task->setCompleted();
    else {
        SpecificEventsContainer progs = getProgrammations(task);
        bool ok = true;
        for (SpecificEventsContainer::iterator it = progs.begin(); it!=progs.end(); ++it) {
            if (!((*it)->isAchieved())) {
                ok = false;
                break;
            }
        }
        if (ok) task->setCompleted();
    }
    if (task->isTaskCompleted()) {
        CompositeTask* parent = CompositeFactory::getInstance().isTaskIncluded(task->getId());
        if (parent) { array = parent->getSubTasksArray();
        bool allCompleted = true;
        Task* temp;
        for (TasksContainer::iterator it = array.begin(); it!=array.end(); ++it) {
            temp = *it;
            if (!(temp->isTaskCompleted())) {
                allCompleted = false;
                break;
            }
        }
        if (allCompleted) parent->setCompleted();
        }
    }
}
