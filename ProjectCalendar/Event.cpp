#include "Event.h"


template<>
Handler<ActivityFactory> Singleton<ActivityFactory>::handler = Handler<ActivityFactory>();

std::vector<Event*>* EventsArray::globalEvents = new std::vector<Event*>();

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

Activity& ActivityFactory::addActivity(QString &n, const QDate &d, const QTime& ti,const Duration& du, const QString &p, const ActivityType &t, const ParticipantsContainer &par) {
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
