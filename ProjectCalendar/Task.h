#ifndef TASK_H
#define TASK_H
#include "Calendar.h"

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
    virtual void setTaskType() {}
    Task(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        identifier(id), title(t), duration(dur), disponibility(dispo), deadline(term), taskType(UNITARY){setTaskType();}
    virtual ~Task(){}
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    enum TaskType taskType;

    template<class T,class F>
    friend class TaskFactory;

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


class UnitaryTask: public Task {
    UnitaryTask(const UnitaryTask& t);
    UnitaryTask& operator=(const UnitaryTask& t);
protected:
    UnitaryTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        Task(id,t,dur,dispo,term), subType(NOT_PREEMPTIVE){setPreemptive();}
    virtual ~UnitaryTask(){}
    void setTaskType() override {taskType = UNITARY;}
    enum UnitarySubTypes subType;
    virtual void setPreemptive() = 0;

    template<class T,class F>
    friend class TaskFactory;

public:
    virtual bool isPreemptive() const=0;
    enum UnitarySubTypes getUnitarySubType() const {return subType;}
};

class PreemptiveTask: public UnitaryTask {
    PreemptiveTask(const PreemptiveTask& t);
    PreemptiveTask& operator=(const PreemptiveTask& t);
protected:
    PreemptiveTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        UnitaryTask(id,t,dur,dispo,term){}
    virtual ~PreemptiveTask();
    void setPreemptive() {subType = PREEMPTIVE;}

    template<class T,class F>
    friend class TaskFactory;
public:
    bool isPreemptive() const {return true;}
    void setInterruption();
};

class NonPreemptiveTask: public UnitaryTask {
    NonPreemptiveTask(const NonPreemptiveTask& t);
    NonPreemptiveTask& operator=(const PreemptiveTask& t);
protected:
    NonPreemptiveTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        UnitaryTask(id,t,dur,dispo,term){}
    virtual ~NonPreemptiveTask();
    void setPreemptive() {subType = NOT_PREEMPTIVE;}

    template<class T,class F>
    friend class TaskFactory;
public:
    bool isPreemptive() const {return false;}
};


class CompositeTask: public Task {
    CompositeTask(const CompositeTask& t);
    CompositeTask& operator=(const CompositeTask& t);
protected:
    TasksContainer subTasks;

    CompositeTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        Task(id,t,dur,dispo,term){}
    virtual ~CompositeTask(); //ask CompositeFactory to destroy the subTasks
    void setTaskType() override {taskType = COMPOSITE;}
    TasksContainer getSubTasksArray() const {return subTasks;}

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
     * this method destroys the subtask using TaskFactory::removeTask method
       and updates the composite-task's array of subtasks
     */
    void removeSubTask(const QString& id);
    Task& getSubTask(const QString& id);
    bool isSubTaskHere(const QString& id) const;
};


class TasksArray {
protected:
    /*!
     * \brief tasks
     * This array of task addresses is unique and shared with anyother
       TaskFactory. It holds the addresses of all the tasks, no matter
       its type.
     */
    static TasksContainer tasks;
};

template<class Factory>
struct Handler {
    Factory* instance;
    Handler():instance(0) {}
    ~Handler(){if (instance) delete[] instance;}
};

template<class T, class F>
class TaskFactory: public TasksArray {
    TaskFactory(const TaskFactory& tf);
    TaskFactory& operator=(const TaskFactory& tf);

protected:
    TaskFactory(){}
    QString file;
    void addItem(Task* t);
    Task* findTask(const QString& id) const {
        for (typename F::TasksIterator it = F::getInstance().getIterator(); !(it.isDone()); it.next()) {
            qDebug()<<"blabla";
            qDebug()<<it.current().getId();  // problème avec l'iterateur -> mettre plein de qDebug.
            qDebug()<<"bloblo";
            if (it.current().getId()==id) return &(it.current());
        }
        return 0;
    }

    virtual enum TaskType specificTaskType() const = 0;
    template<class Fa>
    friend struct Handler;  //every Handler<Fa> is a friend of TaskFactory

    static Handler<F> handler;
public:
    virtual ~TaskFactory();
    static F& getInstance() {
        qDebug()<<"Ici ? 1";
        if (handler.instance==0) handler.instance = new F;
        qDebug()<<"Ici ? 2";
        return *(handler.instance);
    }

    void freeInstance();
    T& addTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term) {
        if (isTaskHere(id)) throw CalendarException("Error : Task "+id+" already added");
        T* to_add = new T(id,t,dur,dispo,term);
        tasks.push_back(to_add);
        return *to_add;
    }

    Task& getTask(const QString& id) {
        Task* to_send = findTask(id);
        if (to_send==0) throw CalendarException("Error : Task "+id+" not found");
        return *to_send;
    }

    const Task& getTask(const QString& id) const { // so that it could be used in const methods that shouldn't modify the task
        return const_cast<Task>(getTask(id));
    }

    bool isTaskHere(const QString& id) const {return findTask(id) != 0;}
    void load(const QString& f);
    void save(const QString& f);
    virtual void removeTask(Task* t);

    // ITERATORS

    /*!
     * \brief The TasksIterator class
     * This is a global Iterator shared by every Task Factory. It makes
       iterating on the whole set of tasks possible from any Task Factory.
     */
    class TasksIterator {
    protected:
        TasksIterator(TasksContainer t) : currentTask(t){}
        TasksContainer currentTask;
        friend class TaskFactory;
    public:
        TasksIterator() : currentTask(0){}
        bool isDone() const { return currentTask.size()==0;}
        virtual void next();
        Task& current() const {
            if (isDone()) throw CalendarException("Error, indirection on a finished iterator");
            return *currentTask[currentTask.size()];
        }

    };


    /*!
     * \brief getIterator
     * \param ct Any Task Iterator should be able to get a Composite Task as a parameter, so that
    we could iterate on the sub-Tasks of this composite Task.
     * \return
     */
    TasksIterator getIterator(const CompositeTask* ct = 0) {
        if (ct) return TasksIterator(ct->getSubTasksArray());
        else return TasksIterator(tasks);
    }

    /*!
     * \brief The TypedTasksIterator class
     * This is a specific Iterator that can be used by any concrete Task Factory
       to iterate on the specific tasks of its main type.
     */
    class TypedTasksIterator : public TasksIterator {
        TypedTasksIterator(TasksContainer t) : TasksIterator(t){}
        friend class TaskFactory;
    public:
        TypedTasksIterator(): TasksIterator(0) {}
        void next() override;
    };

    TypedTasksIterator getTypedTasksIterator(CompositeTask& ct = 0) {
        if (ct) return TypedTasksIterator(ct.getSubTasksArray());
        else return TypedTasksIterator(tasks);
    }
};

class CompositeFactory : public TaskFactory<CompositeTask, CompositeFactory> {
    CompositeFactory(const CompositeFactory& cf);
    CompositeFactory& operator=(const CompositeFactory& cf);
public:
    CompositeFactory():TaskFactory(){qDebug()<<"Ici ? 3";}
    enum TaskType specificTaskType() const {return COMPOSITE;}
    //friend class TaskFactory;
public:
    virtual ~CompositeFactory(){}
    void freeInstance() {this->freeInstance();}
};

template <class T2, class F2>
class UnitaryFactory : public TaskFactory <T2, F2> {
    UnitaryFactory(const UnitaryFactory& cf);
    UnitaryFactory& operator=(const UnitaryFactory& cf);
protected:
    UnitaryFactory():TaskFactory<T2,F2>(){}
    enum TaskType specificTaskType() const override {return UNITARY;}
    virtual enum UnitarySubTypes specificTaskSubType() const = 0;
public:
    virtual ~UnitaryFactory(){}
    class SubTypedTasksIterator : public TaskFactory<T2,F2>::TasksIterator {
        SubTypedTasksIterator(TasksContainer t) : TaskFactory<T2,F2>::TasksIterator(t){}
        friend class UnitaryFactory;
    public:
        SubTypedTasksIterator() : TaskFactory<T2,F2>::TasksIterator(0){}
        void next();
    };
    SubTypedTasksIterator getSubTypedTasksIterator(CompositeTask& ct = 0) {
        if (ct) return SubTypedTasksIterator(ct.getSubTasksArray());
        else return SubTypedTasksIterator(this->tasks);
    }
};

class PreemptiveFactory : public UnitaryFactory <PreemptiveTask, PreemptiveFactory> {
    PreemptiveFactory(const PreemptiveFactory& cf);
    PreemptiveFactory& operator=(const PreemptiveFactory& cf);
protected:
    PreemptiveFactory():UnitaryFactory(){}
    enum UnitarySubTypes specificTaskSubType() const override {return PREEMPTIVE;}
    friend class TaskFactory<PreemptiveTask, PreemptiveFactory>;
public:
    virtual ~PreemptiveFactory(){}
};

class NonPreemptiveFactory : public UnitaryFactory <NonPreemptiveTask, NonPreemptiveFactory> {
    NonPreemptiveFactory(const NonPreemptiveFactory& cf);
    NonPreemptiveFactory& operator=(const NonPreemptiveFactory& cf);
protected:
    NonPreemptiveFactory():UnitaryFactory(){}
    enum UnitarySubTypes specificTaskSubType() const override {return NOT_PREEMPTIVE;}
    friend class TaskFactory<NonPreemptiveTask, NonPreemptiveFactory>;
public:
    virtual ~NonPreemptiveFactory(){}
};


#endif // TASK_H
