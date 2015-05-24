#ifndef TASK_H
#define TASK_H
#include "Calendar.h"
#include "Singleton.h"
#include "Iterator.h"
#include "Association.h"

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

    void checkCompositionValidity();
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

class Association {
    Task* predecessor;
    Task* successor;

    Association():predecessor(0),successor(0){}
    Association(Task* p, Task* s): predecessor(p),successor(s){}
    Association& operator=(const Association& a);
    ~Association(){}

    friend class AssociationManager;
public:
    Task* getPredecessor() const {return predecessor;}
    Task* getSuccessor() const {return successor;}
};

typedef Iterator<Association> AssociationIterator;
typedef std::vector<Association*> AssociationsContainer;

class AssociationManager: public Singleton<AssociationManager>, public Aggregator<Association> {
    AssociationsContainer assos;

    AssociationManager():Aggregator<Association>(&assos){}
    AssociationManager(const AssociationManager& a);
    AssociationManager& operator=(const AssociationManager& a);
    ~AssociationManager(){}
    void fillQueue(std::queue<Task*>& q, TasksContainer tc);
    bool isTaskXFollowedByY(Task* X,Task* Y);
    void removeTaskAssociationLinks(Task* t);

    friend class Singleton<AssociationManager>;
    friend class Handler<AssociationManager>;
    template<class anytask,class anyfactory>
    friend class TaskFactory; // friendship to allow taskFactory to call removeTaskAssociationLinks when removing a task.

public:
    Association& addAssociation(Task* p, Task* s);  // many verifications to do
    void removeAssociation(Task* p, Task* s);
    TasksContainer getTaskPredecessors(Task* t);
    TasksContainer getTaskSuccessors(Task* t);
};

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

    /*!
     * \brief checkCompositionValidity
     * This method checks if this task is included or not by a Composite Task.
       If there is a Composite Task including this taks, then this method calls
       removeSubTask in order to keep the subTasks arrays valid.
       This method allows us to not check for subTask's validy every time we want to use it.
     * Important: If CompositeTask is no longer effective, then simply remove this method.
     */

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

class TasksArray {
private:
    /*!
     * \brief tasks
     * This array of task addresses is unique and shared with anyother
       TaskFactory. It holds the addresses of all the tasks, no matter
       its type.
     */
    static TasksContainer* tasks;
    static unsigned int nbFactories; // the number of Factories currently existing
    template<class any, class way>
    friend class TaskFactory;
};

template<class T, class F>
class TaskFactory: public Singleton<F>, public Aggregator<Task> {
    TaskFactory(const TaskFactory& tf);
    TaskFactory& operator=(const TaskFactory& tf);
    //TasksArray* tasksArray;

protected:

    TaskFactory():file(""),tasks(TasksArray::tasks),Aggregator<Task>(TasksArray::tasks){TasksArray::nbFactories ++;}
    virtual ~TaskFactory() {
        //if (file!="") this->save(file);
        TasksArray::nbFactories --;  // reminder : TasksArray::nbFactories is a static variable
        if (TasksArray::nbFactories==0) {
            while(!(tasks->empty())) removeTask(tasks->front());
            tasks->clear();
        }
        file="";
    }
    QString file;
    TasksContainer* tasks;

    void addItem(Task* t) {
        tasks->push_back(t);
    }

    Task* findTask(const QString& id) const {
        for (TasksContainer::iterator it = tasks->begin(); it!=tasks->end(); ++it) {
            if ((*it)->getId()==id) return *it;
        }
        return 0;
    }

    void checkAssociationValidity(Task* t) {
        AssociationManager* am = AssociationManager::getInstance();
        for (AssociationIterator it = am->getIterator(); !(it.isDone()); it.next()) {

        }
    }

    friend class Singleton<F>;  //every Handler<Fa> is a friend of TaskFactory

public:
    typedef Iterator<T> TypedTasksIterator;
    virtual enum TaskType specificTaskType() const=0;


    T& addTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term) {
        if (isTaskHere(id)) throw CalendarException("Error : Task "+id+" already added");
        T* to_add = new T(id,t,dur,dispo,term);
        tasks->push_back(to_add);
        return *to_add;
    }

    Task& getTask(const QString& id) {
        Task* to_send = findTask(id);
        if (to_send==0) throw CalendarException("Error : Task "+id+" not found");
        return *to_send;
    }

    T& getTypedTask(const QString& id) {
        T* toSend = dynamic_cast<T*>(&(getTask(id)));
        if (toSend) return *toSend;
        else throw CalendarException("Error : Type of Task "+id+" and asked type don't match");
    }

    const Task& getTask(const QString& id) const { // so that it could be used in const methods that shouldn't modify the task
        return const_cast<Task>(getTask(id));
    }

    const T& getTypedTask(const QString &id) const {
        return const_cast<T>(getTypedTask(id));
    }

    bool isTaskHere(const Task* const id) const {
        for (TasksContainer::iterator it = tasks->begin(); it!=tasks->end(); ++it) {
            if (id==*it) return true;
        }
        return false;
    }


    bool isTaskHere(const QString& id) const {return findTask(id) != 0;}
    void load(const QString& f);
    void save(const QString& f);
    void removeTask(Task* t) {
        for (TasksContainer::iterator it = tasks->begin(); it!=tasks->end(); ++it) {
            if (t && *it==t) {
                AssociationManager::getInstance().removeTaskAssociationLinks(*it);
                (*it)->checkCompositionValidity();
                delete *it;
                break;
            }
        }
        for (TasksContainer::iterator it = tasks->begin(); it!=tasks->end(); ++it) { // we have to look for the right "it" one more time because if we delete a composite task, it will delete also its subTasks : tasks array will be reduced and it won't be valid anymore.
            if (t && *it==t) {
                tasks->erase(it);
                return;
            }
        }
    }

    template<int Y,int M,int D>  // Y : year, M : month, D : day
    class DispoTasksIterationStrategy : public TasksIterationStrategy {
        bool test(Task* tested) const override {
            return tested->getDisponibility()>=QDate(Y,M,D);
        }
    };


    TypedTasksIterator getTypedTasksIterator(const TasksIterationStrategy* strategy = 0) {
        return this->template getIterator<T>(strategy);
    }


};

class CompositeFactory : public TaskFactory<CompositeTask, CompositeFactory> {
    CompositeFactory(const CompositeFactory& cf);
    CompositeFactory& operator=(const CompositeFactory& cf);
protected:
    CompositeFactory():TaskFactory(){}
    virtual ~CompositeFactory(){}
    friend class Singleton<CompositeFactory>;
    friend class Handler<CompositeFactory>;
public:
    CompositeTask* isTaskIncluded (const QString& id);
    enum TaskType specificTaskType() const override {return COMPOSITE;}
};

template <class T2, class F2>
class UnitaryFactory : public TaskFactory <UnitaryTask, F2> {
    UnitaryFactory(const UnitaryFactory& cf);
    UnitaryFactory& operator=(const UnitaryFactory& cf);
protected:
    UnitaryFactory():TaskFactory<UnitaryTask,F2>(){}
public:
    typedef Iterator<T2> SubTypedTasksIterator;
    virtual ~UnitaryFactory(){}
    enum TaskType specificTaskType() const override {return UNITARY;}
    virtual enum UnitarySubTypes specificTaskSubType() const = 0;

    SubTypedTasksIterator getSubTypedTasksIterator() {
        return this->template getIterator<T2>();
    }

    /*!
     * \brief addTask
     * \param id
     * \param t
     * \param dur
     * \param dispo
     * \param term
     * \return
     * This is a redefinition of TaskFactory's addTask method made to get the right Task type, and so that
       we prevent TaskFactory to produce (new ...) UnitaryTask objects (UnitaryTask is abstract).
     */
    T2& addTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term) {
        if (this->isTaskHere(id)) throw CalendarException("Error : Task "+id+" already added");
        T2* to_add = new T2(id,t,dur,dispo,term);
        this->addItem(to_add);
        return *to_add;
    }

    T2& getSubTypedTask(const QString& id) {
        T2* toSend = dynamic_cast<T2*>(&(this->getTask(id)));
        if (toSend) return *toSend;
        else throw CalendarException("Error : Type of Task "+id+" and asked subtype don't match");
    }
    const T2& getSubTypedTask(const QString &id) const {
        return const_cast<T2>(getSubTypedTask(id));
    }

    class PreemptiveTasksIterationStrategy : public TasksIterationStrategy {
        bool test(Task* tested) const override {
            UnitaryTask* toTest = dynamic_cast<UnitaryTask*>(tested);
            return toTest->isPreemptive();
        }
    };
};

class PreemptiveFactory : public UnitaryFactory <PreemptiveTask, PreemptiveFactory> {
    PreemptiveFactory(const PreemptiveFactory& cf);
    PreemptiveFactory& operator=(const PreemptiveFactory& cf);
protected:
    PreemptiveFactory():UnitaryFactory(){}
    virtual ~PreemptiveFactory(){}
    friend class Singleton<PreemptiveFactory>;
    friend class Handler<PreemptiveFactory>;
public:
    enum UnitarySubTypes specificTaskSubType() const override {return PREEMPTIVE;}
};

class NonPreemptiveFactory : public UnitaryFactory <NonPreemptiveTask, NonPreemptiveFactory> {
    NonPreemptiveFactory(const NonPreemptiveFactory& cf);
    NonPreemptiveFactory& operator=(const NonPreemptiveFactory& cf);
protected:
    NonPreemptiveFactory():UnitaryFactory(){}
    virtual ~NonPreemptiveFactory(){}
    friend class Singleton<NonPreemptiveFactory>;
    friend class Handler<NonPreemptiveFactory>;
public:
    enum UnitarySubTypes specificTaskSubType() const override {return NOT_PREEMPTIVE;}
};


#endif // TASK_H
