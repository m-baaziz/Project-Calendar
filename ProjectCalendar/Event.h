#ifndef EVENT_H
#define EVENT_H
#include "Singleton.h"
#include "Iterator.h"

class User {
};

class UsersArray {
private:
    /*!
     * \brief users
     * This array of user addresses is unique and shared with anyother
       EventFactory. It holds the addresses of all the users, no matter
       its type.
     */
    static std::vector<User*>* users;
    template<class any, class way>
    friend class EventFactory;
};

class Event {
    template<class C, class V>
    friend class EventFactory;

};

class Activity : public Event {
    template<class C, class V>
    friend class EventFactory;
};

template<class E, class F>
class EventFactory : public Singleton<F>, public Aggregator<E> {
    EventFactory(const EventFactory& ef);
    EventFactory& operator=(const EventFactory& ef);

    friend class Singleton<F>;
protected:
    virtual ~EventFactory(){}
    std::vector<E*> events;
    EventFactory():Aggregator<E>(&events){}
public:
    void updateEvent();
    virtual E& addEvent() =0;
    void removeEvent();
    void save();
    void load();
};

class ActivityFactory : public EventFactory<Activity,ActivityFactory> {
    ActivityFactory(const ActivityFactory& af);
    ActivityFactory& operator=(const ActivityFactory& af);

    friend class Singleton<ActivityFactory>;
    friend class Handler<ActivityFactory>;
protected:
    ActivityFactory() {}
public:
    Activity& addEvent() override {}
};

#endif // EVENT_H
