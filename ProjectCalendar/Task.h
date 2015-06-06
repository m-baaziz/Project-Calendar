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
    Task(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        identifier(id), title(t), duration(dur), disponibility(dispo), deadline(term), isCompleted(false){
        if (id.size()==0 || t.size()==0) throw CalendarException("Error : a Task has to have an id and a title");
        if (dispo>term) throw CalendarException("Error : a Task disponibility can't come after its deadline");
    }
    virtual ~Task(){}
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    bool isCompleted;

    void setCompleted() {isCompleted = true;}   // when a programmation has been done, ProgrammationManager has to set the task as completed.
                                                // a programmationManager can't really set a programmation for a CompositeTask, it has to set them for its subtasks
    template<class T,class F>                   // a programmationManager when setting a programmation has to check Associations constraints.
    friend class TaskFactory;                   // completed tasks have special treatments (special displaying for exemple ...)
                                                // when a task is completed, check if it is a final task of a project, of yes, then set the Project as completed.

public:
    QString getId() const {return identifier;}
    QString getTitle() const {return title;}
    Duration getDuration() const {return duration;}
    QDate getDisponibility() const {return disponibility;}
    QDate getDeadline() const {return deadline;}
    virtual enum TaskType getTaskType() const =0;

    void setId(const QString& id) {identifier=id;}
    void setTitle(const QString& t) {title=t;}
    void setDuration(const Duration& d) {duration=d;}
    void setDisponibility(const QDate& dispo) {disponibility=dispo;}
    void setDeadline(const QDate& date) {deadline=date;}
};

typedef std::vector<Task*> TasksContainer;
typedef Iterator<Task> TasksIterator;
typedef IterationStrategy<Task> TasksIterationStrategy;


class UnitaryTask: public Task {
    UnitaryTask(const UnitaryTask& t);
    UnitaryTask& operator=(const UnitaryTask& t);
protected:
    UnitaryTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        Task(id,t,dur,dispo,term){}
    virtual ~UnitaryTask(){}
    enum TaskType getTaskType() const {return UNITARY;}

    template<class T,class F>
    friend class TaskFactory;

public:
    virtual bool isPreemptive() const=0;
    virtual enum UnitarySubTypes getUnitarySubType() const = 0;
};

// A Preemptive Task can not be turned into a NonPreemptive Task. The same in the other way.

class PreemptiveTask: public UnitaryTask {
    PreemptiveTask(const PreemptiveTask& t);
    PreemptiveTask& operator=(const PreemptiveTask& t);
protected:
    PreemptiveTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        UnitaryTask(id,t,dur,dispo,term), progression(0){}
    virtual ~PreemptiveTask();
    float progression;                 // when a programmation is set for a preemptive task, programmationManager has to know how much this programmation is supposed to increase the task's progression
                                       // when a programmation is completed, it will increase the preemptive task's progression, if progression reaches 100, ProgrammtionManager sets the task as completed.
    template<class T,class F>
    friend class UnitaryFactory;
public:
    bool isPreemptive() const {return true;}
    enum UnitarySubTypes getUnitarySubType() const {return PREEMPTIVE;}
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
        UnitaryTask(id,t,dur,dispo,term){if(dur.getDurationInHours()>12) throw CalendarException("Error : a non preemptive Task can't last more than 12 hours");}
    virtual ~NonPreemptiveTask();

    template<class T,class F>
    friend class UnitaryFactory;
public:
    bool isPreemptive() const {return false;}
    enum UnitarySubTypes getUnitarySubType() const {return NOT_PREEMPTIVE;}
};


class CompositeTask: public Task, public Aggregator<Task> {
    CompositeTask(const CompositeTask& t);
    CompositeTask& operator=(const CompositeTask& t);

protected:
    TasksContainer  subTasks;
    enum TaskType getTaskType() const {return COMPOSITE;}

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
        Task(id,t,dur,dispo,term),subTasks(TasksContainer()),Aggregator(&subTasks){}
    virtual ~CompositeTask(); //ask CompositeFactory to destroy the subTasks
    void fillQueue(std::queue<SubTaskCouple>& qu,const TasksContainer& st,CompositeTask* includer) const;

    template<class T,class F>
    friend class TaskFactory;

public:
    /*!
     * \brief isValidSubTask
     * \param t
     * \return
     * This method return true if the task t would be a valid subtask and throws an error
       otherwise.
     */
    bool isValidSubTask(Task& t);

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
