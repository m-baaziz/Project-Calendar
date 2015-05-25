#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include "Event.h"
#include "Task.h"

// addProgrammation
// removeProgrammation

class Programmation : public Event {
    template<class C, class V>
    friend class EventFactory;
};

class ProgrammationFactory : public EventFactory<Programmation,ProgrammationFactory> {
    ProgrammationFactory(const ProgrammationFactory& pf);
    ProgrammationFactory& operator=(const ProgrammationFactory& pf);

    friend class Singleton<ProgrammationFactory>;
    friend class Handler<ProgrammationFactory>;
protected:
    ProgrammationFactory(){}
public:
    bool isScheduled(const QString& id);
    Programmation& addEvent() override {}
};

#endif // PROGRAMMATION_H
