#include "Event.h"


template<>
Handler<ActivityFactory> Singleton<ActivityFactory>::handler = Handler<ActivityFactory>();

std::vector<Event*>* EventsArray::globalEvents = new std::vector<Event*>();


ActivityType getActivityType(const QString &type) {
    int i = 0;
    for (QStringList::iterator it = activityTypeTable.begin(); it!=activityTypeTable.end(); ++it) {
        if (*it == type) return ActivityType(i);
        i++;
    }
    throw CalendarException("Error : incorrect activity type");
}


void Event::unregisterParticipant(const QString &username){
    for (ParticipantsContainer::iterator it = participants.begin(); it!=participants.end(); ++it){
        if ((*it)==username) participants.erase(it);
        return;
    }
    throw CalendarException("Error : Participant "+username+" not found");
}

bool Event::isParticipantHere(const QString &username) {
    for (ParticipantsContainer::iterator it = participants.begin(); it!=participants.end(); ++it) {
        if ((*it)==username) return true;
    }
    return false;
}

void Event::registerParticipant(const QString &username) {
    if (!isParticipantHere(username)) participants.push_back(username);
    else throw CalendarException("Error : User already registered");
}

Activity& ActivityFactory::addActivity(const QString &n, const QDate &d, const QTime& ti,const Duration& du, const QString &p, const ActivityType &t, const ParticipantsContainer &par) {
    if (n.size()==0 || p.size()==0) throw CalendarException("Error : Invalid parameters");
    qDebug()<<"name : "+n;
    if (isEventHere(n)) throw CalendarException("Error : Activity "+n+" has already been added");
    if (!isTimeZoneFree(d,ti,du)) throw CalendarException("Error : Time zone not available");
    Activity* newActivity = new Activity(n,d,ti,du,p,t,par);
    events.push_back(newActivity);
    globalEvents->push_back(newActivity);
    return *newActivity;
}

void ActivityFactory::achieveEvent(const QString &name) {
    Activity* toAchieve = findEvent(name);
    toAchieve->setToAchieved();
}
