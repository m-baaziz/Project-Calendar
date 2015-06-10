#ifndef EVENT_H
#define EVENT_H
#include "Singleton.h"
#include "Iterator.h"

typedef QStringList ParticipantsContainer;
typedef enum ActivityTypes {MEETING,APPOINTMENT} ActivityType;
static QStringList activityTypeTable = {"meeting","appointment"};

ActivityType getActivityType(const QString& type);

class Event {
    Event(const Event& e);
    Event& operator=(const Event& e);
protected:
    QString name;
    QDate date;
    QTime time;
    Duration duration;
    QString place;
    ParticipantsContainer participants;
    bool achieved;

    Event(const QString& n, const QDate& d, const QTime& t, const Duration& du, const QString& p, const ParticipantsContainer& par = ParticipantsContainer()) :
        name(n),date(d),time(t),duration(du),place(p),participants(par),achieved(false) {}
    virtual ~Event(){}

    void setToAchieved() {achieved = true;}
public:
    QString getName() {return name;}
    QString getPlace() {return place;}
    QDate getDate() {return date;}
    QTime getTime() {return time;}
    Duration getDuration() {return duration;}
    ParticipantsContainer getParticipants() {return participants;}
    bool isAchieved() {return achieved;}

    void setName(const QString& n) {name = n;}
    void setPlace(const QString& p) {place = p;}
    void setParticipants(const ParticipantsContainer& pc) {participants=pc;}
    bool isParticipantHere(const QString& username);
    void registerParticipant(const QString& username);
    void unregisterParticipant(const QString& username);
    template<class C, class V>
    friend class EventFactory;
};

class Activity : public Event {
    ActivityType type;

    friend class ActivityFactory;

    Activity(const QString& n,const QDate& d, const QTime& ti,const Duration& du, const QString& p,const ActivityType& t, const ParticipantsContainer& par = ParticipantsContainer()) :
        Event(n,d,ti,du,p,par), type(t) {}
    Activity(const Activity& a);
    Activity& operator=(const Activity& a);
    ~Activity(){}
public:
    ActivityType getActivityType() {return type;}
};

class EventsArray {
    static std::vector<Event*>* globalEvents;
    template<class A,class B>
    friend class EventFactory;
};

typedef std::vector<Event*> SimpleEventsContainer;

template<class E, class F>
class EventFactory : public Singleton<F>, public Aggregator<E> {
    EventFactory(const EventFactory& ef);
    EventFactory& operator=(const EventFactory& ef);

    friend class Singleton<F>;
protected:
    typedef std::vector<E*> EventsContainer;
    typedef IterationStrategy<Event> EventsIterationStrategy;

    virtual ~EventFactory(){
        while (!(events.empty())) {
            Event* toDelete = events.back();
            events.pop_back();
            delete toDelete;
        }
    }
    EventsContainer events;
    SimpleEventsContainer* globalEvents;
    EventFactory():globalEvents(EventsArray::globalEvents),Aggregator<E>(&events){}
    E* findEvent(const QString& name) {
        for (typename EventsContainer::iterator it = events.begin(); it != events.end(); ++it)
            if ((*it)->name==name) return *it;
        return 0;
    }

public:
    bool isEventHere(const QString& name) {
        return findEvent(name)!=0;
    }

    E& getEvent(const QString& name) {
        E& toSend = *findEvent(name);
        if (!toSend) throw CalendarException("Error : event "+name+" not found");
        return toSend;
    }
    void removeEvent(const QString& name) {
        Event* toDelete = findEvent(name);
        for (typename EventsContainer::iterator it = events.begin(); it != events.end(); ++it) {
            if (*it==toDelete) {
                delete toDelete;
                events.erase(it);
                for (typename SimpleEventsContainer::iterator it2 = globalEvents->begin(); it2!=globalEvents->end(); ++it2) {
                    if (*it2==*it) {
                        globalEvents->erase(it2);
                        return;
                    }
                }
                return;
            }
        }
        throw CalendarException("Error : event "+name+" not found");
    }
    virtual void achieveEvent(const QString& name) = 0;

    SimpleEventsContainer getEventsByDate(const QDate& d) {
        EventsContainer toSend = EventsContainer();
        for (typename SimpleEventsContainer::iterator it = globalEvents->begin(); it!=globalEvents->end(); ++it)
            if ((*it)->getDate() == d) toSend.push_back(*it);
        return toSend;
    }
    Event* getEventByDateAndTime(const QDate& d, const QTime& t) {
        Event* toSend = 0;
        for (typename SimpleEventsContainer::iterator it = globalEvents->begin(); it!=globalEvents->end(); ++it) {
            if ((*it)->getDate()==d && (*it)->getTime()==t) toSend =*it;
            return toSend;
        }
    }

    EventsContainer getSpecificEventsByDate(const QDate& d) {
        EventsContainer toSend = EventsContainer();
        for (typename EventsContainer::iterator it = events.begin(); it!=events.end(); ++it)
            if ((*it)->getDate() == d) toSend.push_back(*it);
        return toSend;
    }
    E* getSpecificEventByDateAndTime(const QDate& d, const QTime& t) {
        E* toSend = 0;
        for (typename EventsContainer::iterator it = events.begin(); it!=events.end(); ++it) {
            if ((*it)->getDate()==d && (*it)->getTime()==t) {
                toSend=*it;
                break;
            }
        }
        return toSend;
    }


    bool isTimeZoneFree(const QDate& d, const QTime& t, const Duration& du) {
        Event* temp = 0;
        for (typename SimpleEventsContainer::iterator it = globalEvents->begin(); it!=globalEvents->end(); ++it) {
            temp = *it;
            QTime max = QTime(t.hour()+du.getHours(),t.minute()+du.getMinutes());
            if (temp->getDate()==d && temp->getTime()>=t && temp->getTime()<max)
                return false;
        }
        return true;
    }

    void save();
    void load();

    class AchievedEventsIterationStrategy : public EventsIterationStrategy {
        bool test(Event* tested) const {
            return tested->isAchieved();
        }
    };
    class NotAchievedEventsIterationStrategy : public EventsIterationStrategy {
        bool test(Event *tested) const {
            return !(tested->isAchieved());
        }
    };
};

class ActivityFactory : public EventFactory<Activity,ActivityFactory> {
    ActivityFactory(const ActivityFactory& af);
    ActivityFactory& operator=(const ActivityFactory& af);

    friend class Singleton<ActivityFactory>;
    friend class Handler<ActivityFactory>;
protected:
    ActivityFactory() {}
public:
    Activity& addActivity(const QString& n,const QDate& d, const QTime& ti,const Duration& du, const QString& p,const ActivityType& t, const ParticipantsContainer& par);
    void achieveEvent(const QString& name) override;
};

#endif // EVENT_H
