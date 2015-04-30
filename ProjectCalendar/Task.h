#ifndef TASK_H
#define TASK_H
#include "Calendar.h"

/*!
 * \file Task.h
 * \brief Header file that describes the classes related with Tasks Management
 */

/*!
 * \brief The Task class
   Its birth and death are managed only by the TaskManager.
 */
class Task{
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    enum TaskType {UNITARY, COMPOSITE} tasktype;

    Task(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        identifier(id), title(t), duration(dur), disponibility(dispo), deadline(term), tasktype(UNITARY){setTaskType();}
    Task(const Task& t);
    Task& operator=(const Task& t);
    virtual ~Task(){}
    virtual void setTaskType() = 0;

    friend class TaskManger;

public:
    QString getId() const {return identifier;}
    QString getTitle() const {return title;}
    Duration getDuration() const {return duration;}
    QDate getDisponibility() const {return disponibility;}
    QDate getDeadline() const {return deadline;}
    QString getTaskType() const {
        if (tasktype == COMPOSITE) return "composite";
        else return "unitary";
    }

    void setId(const QString& id) {identifier=id;}
    void setTitle(const QString& t) {title=t;}
    void setDuration(const Duration& d) {duration=d;}
    void setDisponibility(const QDate& dispo) {disponibility=dispo;}
    void setDeadline(const QDate& date) {deadline=date;}
};

class UnitaryTask: public Task {
    bool preemptive;

    UnitaryTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        Task(id,t,dur,dispo,term), preemptive(true){setPreemptive();}
    UnitaryTask(const UnitaryTask& t);
    UnitaryTask& operator=(const UnitaryTask& t);
    virtual ~UnitaryTask(){}
    virtual void setPreemptive() = 0;
    void setTaskType(){tasktype = UNITARY;}

    friend class TaskManager;

public:
    bool isPreemptive() const {return preemptive;}

};

class PreemptiveTask: public UnitaryTask {
    PreemptiveTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        UnitaryTask(id,t,dur,dispo,term){}
    PreemptiveTask(const PreemptiveTask& t);
    PreemptiveTask& operator=(const PreemptiveTask& t);
    ~PreemptiveTask(){}
    void setPreemptive() {preemptive = true;}

    friend class TaskManager;

public:
    void setInterruption();
};

class NonPreemptiveTask: public UnitaryTask {
    NonPreemptiveTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        UnitaryTask(id,t,dur,dispo,term){}
    NonPreemptiveTask(const NonPreemptiveTask& t);
    NonPreemptiveTask& operator=(const PreemptiveTask& t);
    ~NonPreemptiveTask(){}
    void setPreemptive() {preemptive = false;}

    friend class TaskManager;
};

class CompositeTask: public Task {
    Task** subTasks;

    CompositeTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        Task(id,t,dur,dispo,term){}
    CompositeTask(const CompositeTask& t);
    CompositeTask& operator=(const CompositeTask& t);
    ~CompositeTask(){}
    void setTaskType(){tasktype = COMPOSITE;}

    friend class TaskManager;

public:
    /*!
     * \brief addSubTask
     * the subtask has to be created before, this method only adds the address
       of this task in the array of subTasks.
     */
    void addSubTask(const Task& t);
    /*!
     * \brief removeSubTask
     * this method destroys the subtask using TaskManager::removeTask method
       and updates the composite-task's array of subtasks
     */
    void removeSubTask(const Task& t);
    Task& getSubTask(const QString& id);
};



class TaskManager {
    Task** tasks;
    unsigned int nb;
    unsigned int max;
    QString file;

    void addItem(Task* t);
    Task* findTask(const QString& id) const;
    TaskManager();
    ~TaskManager();
    TaskManager(const TaskManager& tm);
    TaskManager& operator=(const TaskManager& tm);

    struct Handler {
        TaskManager* instance;
        Handler():instance(0){}
        ~Handler(){if (instance) delete instance;}
    };
    static Handler handler;

public:
    static TaskManager& getInstance();
    static void libererInstance();
    UnitaryTask& addUnitaryTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term,bool preempt = false);
    CompositeTask& addCompositeTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term);
    Task& getTask(const QString& id);
    const Task& getTask(const QString& id) const;    // so that it could be used in const methods that shouldn't modify the task
    bool isTaskHere(const QString& id) const {return findTask(id) != 0;}
    void load(const QString& f);
    void save(const QString& f);

    /* TO DO :
     * Add iterators declarations,
     * Define in Task.cpp all the functions
     * Think about new functions that could be usefull
    */

};

#endif // TASK_H
