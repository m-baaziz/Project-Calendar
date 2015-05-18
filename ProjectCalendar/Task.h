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
    Task(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term, const enum TaskType& type):
        identifier(id), title(t), duration(dur), disponibility(dispo), deadline(term), taskType(type){}
    virtual ~Task(){checkCompositionValidity();}
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    enum TaskType taskType;
    /*!
     * \brief checkCompositionValidity
     * This method checks if this task is included or not by a Composite Task.
       If there is a Composite Task including this taks, then this method calls
       removeSubTask in order to keep the subTasks arrays valid.
       This method allows us to not check for subTask's validy every time we want to use it.
     * Important: If CompositeTask is no longer effective, then simply remove this method.
     */
    void checkCompositionValidity();

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
        UnitaryTask(id,t,dur,dispo,term,PREEMPTIVE){}
    virtual ~PreemptiveTask();

    template<class T,class F>
    friend class UnitaryFactory;
public:
    bool isPreemptive() const {return true;}
    void setInterruption();
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


class CompositeTask: public Task {
    CompositeTask(const CompositeTask& t);
    CompositeTask& operator=(const CompositeTask& t);
protected:
    TasksContainer  subTasks;

    struct SubTaskCouple {
        Task* included;
        CompositeTask* includer;
        SubTaskCouple():included(0),includer(0){}
        SubTaskCouple(Task* son,CompositeTask* father): included(son), includer(father) {}
    };

    CompositeTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term):
        Task(id,t,dur,dispo,term,COMPOSITE), subTasks(TasksContainer()){}
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

template<class Factory>
struct Handler {
    Factory* instance;
    Handler():instance(0) {}
    ~Handler(){if (instance) delete instance;}
};

template<class T, class F>
class TaskFactory {
    TaskFactory(const TaskFactory& tf);
    TaskFactory& operator=(const TaskFactory& tf);
    //TasksArray* tasksArray;

protected:
    TaskFactory():file(""){
       TasksArray::nbFactories ++;
    }
    QString file;
    //TasksContainer* tasks;

    void addItem(Task* t) {
        TasksArray::tasks->push_back(t);
    }

    Task* findTask(const QString& id) const {
        for (TasksContainer::iterator it = TasksArray::tasks->begin(); it!=TasksArray::tasks->end(); ++it) {
            if ((*it)->getId()==id) return *it;
        }
        return 0;
    }
    TasksContainer* getTasksArray() {
        return TasksArray::tasks;
    }

    template<class Fa>
    friend struct Handler;  //every Handler<Fa> is a friend of TaskFactory

    static Handler<F> handler;
public:
    virtual enum TaskType specificTaskType() const=0;
    virtual ~TaskFactory() {
        //if (file!="") this->save(file);
        TasksArray::nbFactories --;  // reminder : TasksArray::nbFactories is a static variable
        if (TasksArray::nbFactories==0) {
            while(!(TasksArray::tasks->empty())) {
                removeTask(TasksArray::tasks->front());
            }
            TasksArray::tasks->clear();
        }
        file="";
    }

    static F& getInstance() {
        if (handler.instance==0) handler.instance = new F;
        return *(handler.instance);
    }

    static void freeInstance() {
        if (handler.instance!=0) delete handler.instance;
        handler.instance = 0;
    }

    T& addTask(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term) {
        if (isTaskHere(id)) throw CalendarException("Error : Task "+id+" already added");
        T* to_add = new T(id,t,dur,dispo,term);
        TasksArray::tasks->push_back(to_add);
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
        for (TasksContainer::iterator it = TasksArray::tasks->begin(); it!=TasksArray::tasks->end(); ++it) {
            if (id==*it) return true;
        }
        return false;
    }
    bool isTaskHere(const QString& id) const {return findTask(id) != 0;}
    void load(const QString& f);
    void save(const QString& f);
    void removeTask(Task* t) {
        for (TasksContainer::iterator it = TasksArray::tasks->begin(); it!=TasksArray::tasks->end(); ++it) {
            if (*it==t) {
                delete *it;
                TasksArray::tasks->erase(it);   // look how to empty correctly a vector
                return;
            }
        }
    }


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
        virtual ~TasksIterator(){}
        bool isDone() const { return currentTask.size()==0;}
        void next(){
            if (isDone()) throw CalendarException("Error : next on a finished iterator");
            currentTask.pop_back();
        }

        Task& current() const {
            if (isDone()) throw CalendarException("Error, indirection on a finished iterator");
            return *currentTask.back();
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
        else return TasksIterator(*TasksArray::tasks);
    }

    /*!
     * \brief The TypedTasksIterator class
     * This is a specific Iterator that can be used by any concrete Task Factory
       to iterate on the specific tasks of its main type.
     */
    class TypedTasksIterator : public TasksIterator {
        TypedTasksIterator(TasksContainer t) : TasksIterator(t){
            for (TasksContainer::iterator it = this->currentTask.begin(); it!=this->currentTask.end();) {
                if ((*it)->getTaskType()!=F::getInstance().specificTaskType()) {
                    this->currentTask.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
        friend class TaskFactory;
    public:
        TypedTasksIterator(): TasksIterator(0) {}
        T& current() const {
            if (this->isDone()) throw CalendarException("Error, indirection on a finished iterator");
            Task* taskCurrent = this->currentTask.back();
            T* toSend = dynamic_cast<T*>(taskCurrent);
            return *toSend;
        }
    };

    TypedTasksIterator getTypedTasksIterator(const CompositeTask* ct = 0) {
        if (ct) return TypedTasksIterator(ct->getSubTasksArray());
        else return TypedTasksIterator(*TasksArray::tasks);
    }
};

class CompositeFactory : public TaskFactory<CompositeTask, CompositeFactory> {
    CompositeFactory(const CompositeFactory& cf);
    CompositeFactory& operator=(const CompositeFactory& cf);
protected:
    CompositeFactory():TaskFactory(){}
    friend class TaskFactory<CompositeTask,CompositeFactory>;
public:
    virtual ~CompositeFactory(){}
    enum TaskType specificTaskType() const override {return COMPOSITE;}
};

template <class T2, class F2>
class UnitaryFactory : public TaskFactory <UnitaryTask, F2> {
    UnitaryFactory(const UnitaryFactory& cf);
    UnitaryFactory& operator=(const UnitaryFactory& cf);
protected:
    UnitaryFactory():TaskFactory<UnitaryTask,F2>(){}
public:
    virtual ~UnitaryFactory(){}
    enum TaskType specificTaskType() const override {return UNITARY;}
    virtual enum UnitarySubTypes specificTaskSubType() const = 0;
    class SubTypedTasksIterator : public TaskFactory<T2,F2>::TasksIterator {
        SubTypedTasksIterator(TasksContainer t) : TaskFactory<T2,F2>::TasksIterator(t){
            for (TasksContainer::iterator it = this->currentTask.begin(); it!=this->currentTask.end();) {
                if (!((*it)->getTaskType()==UNITARY && dynamic_cast<UnitaryTask*>(*it)->getUnitarySubType()==F2::getInstance().specificTaskSubType())) this->currentTask.erase(it);
                else {
                    qDebug()<<"type de "+(*it)->getId()+" : ";//+(*it)->getTaskType();
                    ++it;
                }
            }
            qDebug()<<"nombre de current Task : "+QString::number(this->currentTask.size());
        }
        friend class UnitaryFactory;
    public:
        SubTypedTasksIterator() : TaskFactory<T2,F2>::TasksIterator(0){}
        T2& current() const {
            if (this->isDone()) throw CalendarException("Error, indirection on a finished iterator");
            Task* taskCurrent = this->currentTask.back();
            T2* toSend = dynamic_cast<T2*>(taskCurrent);
            if (!toSend) qDebug()<<"toSend est null, taille de currentTask : "+QString::number(this->currentTask.size());
            return *toSend;
        }
    };
    SubTypedTasksIterator getSubTypedTasksIterator(CompositeTask* ct = 0) {
        if (ct) return SubTypedTasksIterator(ct->getSubTasksArray()); // try to factorise all of this
        else return SubTypedTasksIterator(*(this->getTasksArray()));
    }

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
};

class PreemptiveFactory : public UnitaryFactory <PreemptiveTask, PreemptiveFactory> {
    PreemptiveFactory(const PreemptiveFactory& cf);
    PreemptiveFactory& operator=(const PreemptiveFactory& cf);
protected:
    PreemptiveFactory():UnitaryFactory(){}
    friend class UnitaryFactory<PreemptiveTask, PreemptiveFactory>;
    friend class TaskFactory<UnitaryTask, PreemptiveFactory>;
public:
    virtual ~PreemptiveFactory(){}
    enum UnitarySubTypes specificTaskSubType() const override {return PREEMPTIVE;}
};

class NonPreemptiveFactory : public UnitaryFactory <NonPreemptiveTask, NonPreemptiveFactory> {
    NonPreemptiveFactory(const NonPreemptiveFactory& cf);
    NonPreemptiveFactory& operator=(const NonPreemptiveFactory& cf);
protected:
    NonPreemptiveFactory():UnitaryFactory(){}
    friend class UnitaryFactory<NonPreemptiveTask, NonPreemptiveFactory>;
    friend class TaskFactory<UnitaryTask, NonPreemptiveFactory>;
public:
    virtual ~NonPreemptiveFactory(){}
    enum UnitarySubTypes specificTaskSubType() const override {return NOT_PREEMPTIVE;}
};


#endif // TASK_H
