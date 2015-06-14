#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include "Event.h"
#include "Task.h"
#include "Association.h"
#include "QTime"

class ProgrammationFactory : public EventFactory<Programmation,ProgrammationFactory> {
    ProgrammationFactory(const ProgrammationFactory& pf);
    ProgrammationFactory& operator=(const ProgrammationFactory& pf);

    friend class Singleton<ProgrammationFactory>;
    friend class Handler<ProgrammationFactory>;
protected:
    ProgrammationFactory():EventFactory(){}
    ~ProgrammationFactory() {}
public:
    bool isScheduled(UnitaryTask* t);
    /*!
     * \brief scheduleTask
     * \return
     * Adds a programmation to a given Unitary Task;
     */
    Programmation& scheduleTask(UnitaryTask* t,const QString& n,const QDate& d, const QTime& ti,
                                const Duration& du,const QString& p,const ParticipantsContainer& par = ParticipantsContainer());
    /*!
     * \brief getTimeToSchedule
     * \param t
     * \return
     * This method returns a Duration representing the time left (not scheduled yet) of a Preemptive Task.
     */
    Duration getTimeLeftToSchedule(PreemptiveTask* t);
    Programmation* getProgrammation(NonPreemptiveTask* t);
    Programmation* getProgrammation(PreemptiveTask* t, const QDate& d, const QTime& ti);
    /*!
     * \brief getProgrammations
     * \param t
     * \return
     * Method that returns every programmations of a preemptive task.
     */
    SpecificEventsContainer getProgrammations(UnitaryTask* t);
    /*!
     * \brief getProgrammations
     * \param t
     * \param d
     * \return
     * Method that returns every programmations of a preemptive task in a given date.
     */
    SpecificEventsContainer getProgrammations(UnitaryTask *t, const QDate& d);
    /*!
     * \brief getTaskToSchedule
     * \param t
     * \return
     * This method returns an array of Tasks that still need to be scheduled in order to be able to schedule
       the unitary task given.
     */
    TasksContainer getTaskToSchedule(UnitaryTask* t);
    /*!
     * \brief removeProgrammation
     * \param t
     * Removes all programamtions of a unitary task.
     */
    void removeProgrammation(UnitaryTask* t);
    void removeSpecificProgrammation(UnitaryTask* t, const QDate& d, const QTime& ti);
    void achieveEvent(const QString& name) override;
};

#endif // PROGRAMMATION_H
