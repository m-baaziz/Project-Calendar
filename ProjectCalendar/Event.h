#ifndef EVENT_H
#define EVENT_H
#include "Singleton.h"
#include "Iterator.h"

typedef QStringList ParticipantsContainer;
typedef enum ActivityTypes {MEETING,APPOINTMENT,BIRTHDAY} ActivityType;
static QStringList activityTypeTable = {"meeting","appointment","birthday"};
typedef enum EventTypes {ACTIVITY,PROGRAMMATION} EventType;

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
    EventType eventType;
    bool achieved;

    Event(const QString& n, const QDate& d, const QTime& t, const Duration& du, const QString& p, const ParticipantsContainer& par = ParticipantsContainer()) :
        name(n),date(d),time(t),duration(du),place(p),participants(par),achieved(false) {}
    virtual ~Event(){}

    void setToAchieved() {achieved = true;}
public:
    QString getName() const {return name;}
    QString getPlace() const {return place;}
    QDate getDate() const {return date;}
    QTime getTime() const {return time;}
    Duration getDuration() const {return duration;}
    ParticipantsContainer getParticipants() const {return participants;}
    virtual EventType getEventType() const = 0;
    bool isAchieved() const {return achieved;}

    void setName(const QString& n) {name = n;}
    void setPlace(const QString& p) {place = p;}
    void setDate(const QDate& da) {date = da;}
    void setDuration(const Duration& du) {duration = du;}
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
    EventType getEventType() const override {return ACTIVITY;}
    ActivityType getActivityType() const {return type;}
};

class Programmation : public Event {

    UnitaryTask* task;

    Programmation(const QString& n,const QDate& d, const QTime& ti, const QString& p,const Duration& du,UnitaryTask* t,const ParticipantsContainer& par = ParticipantsContainer()) :
        Event(n,d,ti,du,p,par),task(t) {}
    Programmation(const Programmation& p);
    Programmation& operator=(const Programmation& p);
    virtual ~Programmation(){}

    friend class ProgrammationFactory;
public:
    UnitaryTask* getTask() {return task;}
    const UnitaryTask* getTask() const {return task;}
    EventType getEventType() const override {return PROGRAMMATION;}
};

typedef std::list<Event*> EventsContainer;

class EventsArray {
    static EventsContainer* globalEvents;
    template<class A,class B>
    friend class EventFactory;
};


template<class E, class F>
class EventFactory : public Singleton<F>, public Aggregator<Event> {
    EventFactory(const EventFactory& ef);
    EventFactory& operator=(const EventFactory& ef);

    friend class Singleton<F>;
protected:
    typedef IterationStrategy<Event> EventsIterationStrategy;

    virtual ~EventFactory(){
        while (!(events->empty())) {
            Event* toDelete = events->back();
            events->pop_back();
            delete toDelete;
        }
    }
    EventsContainer* events;
    QFile file;
    EventFactory():file(""),events(EventsArray::globalEvents),Aggregator<Event>(EventsArray::globalEvents){}
    Event* findEvent(const QString& name) {
        for (typename EventsContainer::iterator it = events->begin(); it != events->end(); ++it)
            if ((*it)->name==name) return *it;
        return 0;
    }

    void commonSave(QXmlStreamWriter& stream, const Event& e) {
        stream.writeTextElement("name",e.getName());
        stream.writeTextElement("date",e.getDate().toString());
        stream.writeTextElement("time",e.getTime().toString());
        stream.writeTextElement("duration",e.getDuration().toString());
        stream.writeTextElement("place",e.getPlace());
        stream.writeTextElement("participants",e.getParticipants().join(','));
        stream.writeTextElement("achieved",(e.isAchieved())?"true":"false");
    }

    friend void loadAll(const QString& fileName);

public:
    typedef std::list<E*> SpecificEventsContainer;

    void save(QXmlStreamWriter& stream) {
        stream.writeStartElement("Events");
            stream.writeStartElement("Activities");
            for (Iterator<Activity> it=getIterator<Activity>(); !it.isDone(); it.next()) {
                stream.writeStartElement("Activity");
                commonSave(stream,it.current());
                stream.writeTextElement("type",activityTypeTable[it.current().getActivityType()]);
                stream.writeEndElement();
            }
            stream.writeEndElement();
            stream.writeStartElement("Programmations");
            for (Iterator<Programmation> it=getIterator<Programmation>(); !it.isDone(); it.next()) {
                stream.writeStartElement("Programmation");
                commonSave(stream,it.current());
                stream.writeTextElement("task",it.current().getTask()->getId());
                stream.writeEndElement();
            }
            stream.writeEndElement();
        stream.writeEndElement();
    }

    bool isEventHere(const QString& name) {
        return findEvent(name)!=0;
    }
    Event* getEvent(const QString &name) {
        Event* toSend = findEvent(name);
        if (!toSend) throw CalendarException("Error : event "+name+" not found");
        return toSend;
    }

    E* getSpecificEvent(const QString& name) {
        E* toSend = dynamic_cast<E*>(findEvent(name));
        if (!toSend) throw CalendarException("Error : event doesn't belong to the specific type you asked");
        return toSend;
    }

    void removeEvent(const QString& name) {
        Event* toDelete = findEvent(name);
        for (typename EventsContainer::iterator it = events->begin(); it != events->end(); ++it) {
            if (*it==toDelete) {
                delete toDelete;
                events->erase(it);
                return;
            }
        }
        throw CalendarException("Error : event "+name+" not found");
    }
    virtual void achieveEvent(const QString& name) = 0;

    EventsContainer getEventsByDate(const QDate& d) {
        EventsContainer toSend = EventsContainer();
        for (typename EventsContainer::iterator it = events->begin(); it!=events->end(); ++it)
            if ((*it)->getDate() == d) toSend.push_back(*it);
        return toSend;
    }
    Event* getEventByDateAndTime(const QDate& d, const QTime& t) {
        Event* toSend = 0;
        for (typename EventsContainer::iterator it = events->begin(); it!=events->end(); ++it) {
            if ((*it)->getDate()==d && (*it)->getTime()==t) toSend =*it;
            return toSend;
        }
    }

    SpecificEventsContainer getSpecificEventsByDate(const QDate& d) {
        SpecificEventsContainer toSend = SpecificEventsContainer();
        for (Iterator<E> it = getIterator<E>(); !(it.isDone()); it.next())
            if (it.current().getDate() == d) toSend.push_back(&it.current);
        return toSend;
    }
    E* getSpecificEventByDateAndTime(const QDate& d, const QTime& t) {
        E* toSend = 0;
        for (Iterator<E> it = getIterator<E>(); !(it.isDone()); it.next()) {
            if (it.current().getDate()==d && it.current().getTime()==t) {
                toSend=&it.current();
                break;
            }
        }
        return toSend;
    }

    EventsContainer getEventsInTimeZone(const QDate& d, const QTime& t, const Duration& du) {
        EventsContainer toSend = EventsContainer();
        QTime endT, endE;
        for (EventsContainer::iterator it=events->begin(); it!=events->end(); ++it) {
            Event* event = *it;
            endE = event->getDuration()+event->getTime();
            endT = du+t;
            if (!endT.isValid()) endT = QTime(23,59,59);
            if (event->getDate()==d &&
                ((event->getTime()>=t && event->getTime()<endT) ||
                (endE>t && endE<endT) || (event->getTime()<=t && endE>=endT))) {
                toSend.push_back(*it);
            }
        }
        return toSend;
    }

    bool isTimeZoneFree(const QDate& d, const QTime& t, const Duration& du) {
        Event* temp = 0;
        for (typename EventsContainer::iterator it = events->begin(); it!=events->end(); ++it) {
            temp = *it;
            QTime max = du+t;
            if (temp->getDate()==d && temp->getTime()>=t && temp->getTime()<=max)
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
