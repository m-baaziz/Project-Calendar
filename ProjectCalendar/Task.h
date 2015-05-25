#ifndef TASK_H
#define TASK_H
#include "Calendar.h"
#include "Iterator.h"   // for composite Tasks

/*!
 * \file Task.h
 * \brief Header file that describes the classes related with Tasks Management
 */
/*!
 * \brief The TaskType enum
 * Global type declaration so that it can be used by every Task.h's Class.
   This Type enumerates the main Task types.
 */
enum TaskType {UNITARY, COMPOSITE};
enum UnitarySubTypes {PREEMPTIVE, NOT_PREEMPTIVE};

/*!
 * \brief The Task class
   Its birth and death are managed only by the TaskFactory.
 */
class Task{ 
    Task(const Task& t);
    Task& operator=(const Task& t);

protected:
    Task(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term, const enum TaskType& type):
        identifier(id), title(t), duration(dur), disponibility(dispo), deadline(term), taskType(type), isCompleted(false){}
    virtual ~Task(){}
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    enum TaskType taskType;
    bool isCompleted;

    void setCompleted() {isCompleted = true;}   // when a programmation has been done, ProgrammationManager has to set the task as completed.
                                                // a programmationManager can't really set a programmation for a CompositeTask, it has to set them for its subtasks
    template<class T,class F>                   // a programmationManager when setting a programmation has to check Associations constraints.
    friend class TaskFactory;                   // completed tasks have special treatments (special displaying for exemple ...)

public:
    QString getId() const {return identifier;}
    QString getTitle() const {return title;}
    Duration getDuration() const {return duration;}
    QDate getDisponibility() const {return disponibility;}
    QDate getDeadline() const {return deadline;}
    enum TaskType getTaskType() const {return taskType;}

    void setId(const QString& id) {identifier=id;}
    void setTitle(const QString& t) {title=t;}
    void setDuration(const Duration& d) {duration=d;}
    void setDisponibility(const QDate& dispo) {disponibility=dispo;}
    void setDeadline(const QDate& date) {deadline=date;}
};

typedef std::vector<Task*> TasksContainer;
typedef Iterator<Task> TasksIterator;
typedef IterationStrategy<Task> TasksIterationStrategy;

// ******************** ASSOCIATIONS MANAGEMENT ***************************************


// *************************************************************************************************************


class UnitaryTask: public Task {
    UnitaryTask(const UnitaryTask& t);
    UnitaryTask& operator=(const UnitaryTask& t);
protected:
    UnitaryTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term, const enum UnitarySubTypes& subtype):
        Task(id,t,dur,dispo,term,UNITARY), subType(subtype){}
    virtual ~UnitaryTask(){}
    enum UnitarySubTypes subType;

    template<class T,class F>
    friend class TaskFactory;

public:
    virtual bool isPreemptive() const=0;
    enum UnitarySubTypes getUnitarySubType() const {return subType;}
};

// A Preemptive Task can not be turned into a NonPreemptive Task. The same in the other way.

class PreemptiveTask: public UnitaryTask {
    PreemptiveTask(const PreemptiveTask& t);
    PreemptiveTask& operator=(const PreemptiveTask& t);
protected:
    PreemptiveTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        UnitaryTask(id,t,dur,dispo,term,PREEMPTIVE), progression(0){}
    virtual ~PreemptiveTask();
    float progression;                 // when a programmation is set for a preemptive task, programmationManager has to know much this programmation is supposed to increase the task's progression
                                       // when a programmation is completed, it will increase the preemptive task's progression, if progression reaches 100, ProgrammtionManager sets the task as completed.
    template<class T,class F>
    friend class UnitaryFactory;
public:
    bool isPreemptive() const {return true;}
    //void setInterruption();
    void setProgression(const float& p) {
        if (p < 0 || p > 100) throw CalendarException("Error : Invalid progression value (has to be >= 0 and <= 100)");
        if (p < progression) throw CalendarException("Error : a Preemptive Task's progression can't decrease");
        progression = p;
    }
};

class NonPreemptiveTask: public UnitaryTask {
    NonPreemptiveTask(const NonPreemptiveTask& t);
    NonPreemptiveTask& operator=(const PreemptiveTask& t);
protected:
    NonPreemptiveTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        UnitaryTask(id,t,dur,dispo,term,NOT_PREEMPTIVE){}
    virtual ~NonPreemptiveTask();

    template<class T,class F>
    friend class UnitaryFactory;
public:
    bool isPreemptive() const {return false;}
};


class CompositeTask: public Task, public Aggregator<Task> {
    CompositeTask(const CompositeTask& t);
    CompositeTask& operator=(const CompositeTask& t);

protected:
    TasksContainer  subTasks;

    /*!
     * \brief The SubTaskCouple struct
     * Proposes a structure to store a couple of tasks : included and includer.
     * This structure is used in method isSubTaskHere.
     */
    struct SubTaskCouple {
        Task* included;
        CompositeTask* includer;
        SubTaskCouple():included(0),includer(0){}
        SubTaskCouple(Task* son,CompositeTask* father): included(son), includer(father) {}
    };

    CompositeTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        Task(id,t,dur,dispo,term,COMPOSITE),subTasks(TasksContainer()),Aggregator(&subTasks){}
    virtual ~CompositeTask(); //ask CompositeFactory to destroy the subTasks
    void fillQueue(std::queue<SubTaskCouple>& qu,const TasksContainer& st,CompositeTask* includer) const;

    template<class T,class F>
    friend class TaskFactory;

public:
    /*!
     * \brief addSubTask
     * the subtask has to be created before, this method only adds the address
       of this task in the array of subTasks.
     */
    void addSubTask(Task& t);
    /*!
     * \brief removeSubTask
     * \param id
     * This method doesn't delete the sub-task decribed by "id" but simply
       removes the "aggregation link" between this task and the sub-task.
     */
    void removeSubTask(const QString& id);
    Task& getSubTask(const QString& id);
    TasksContainer getSubTasksArray() const {return subTasks;}

    /*!
     * \brief isSubTaskHere
     * \param id
     * \return
     * This method looks at every subTasks (including the sub-tasks of sub-tasks ...)
       to see whether the task described by id is included is this CompositeTask or not.
       If it is included, then the method returns the address of the Task including it,
       otherwise it returns 0.
     */
    CompositeTask* isSubTaskHere(const QString& id);
};



#endif // TASK_H
