#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include "Task.h"
#include "Singleton.h"
#include "Association.h"
#include "Project.h"

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

    /*!
     * \brief checkCompositionValidity
     * This method checks if this task is included or not by a Composite Task.
       If there is a Composite Task including this taks, then this method calls
       removeSubTask in order to keep the subTasks arrays valid.
       This method allows us to not check for subTask's validy every time we want to use it.
     * Important: If CompositeTask is no longer effective, then simply remove this method.
     */
    void checkCompositionValidity(Task* t) {
        CompositeTask* includer;
        for (Iterator<CompositeTask> it = this->template getIterator<CompositeTask>(); !(it.isDone()); it.next()) {
            includer = &(it.current()); // here we can't use the TypedTasksIterator to get only composite Tasks because it will use a redefined pure virtual method, which may cause some trouble if this method is called during CompositeFactory destruction.
            //if (!includer) continue;  // includer=0 when we get this deleted task.
            includer = includer->isSubTaskHere(t->getId());
            if (includer) {
                includer->removeSubTask(t->getId());
                return;
            }
        }
    }

    void checkProjectValidity(Task* t) {
        for (Iterator<Project> it = ProjectFactory::getInstance().getIterator(); !(it.isDone()); it.next()) {
            if ((it.current()).isItemHere(t)) {
                it.current().softRemoveTask(t->getId());
                return;
            }
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

    bool isTaskHere(const Task* const t) const {
        for (TasksContainer::iterator it = tasks->begin(); it!=tasks->end(); ++it) {
            if (t==*it) return true;
        }
        return false;
    }


    bool isTaskHere(const QString& id) const {return findTask(id) != 0;}
    void load(const QString& f);
    void save(const QString& f);
    void removeTask(Task* t) {
        for (TasksContainer::iterator it = tasks->begin(); it!=tasks->end(); ++it) {
            if (t && *it==t) {
                checkProjectValidity(*it);
                AssociationManager::getInstance().removeTaskAssociationLinks(*it);
                checkCompositionValidity(*it);
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
    /*!
     * \brief The NotIncludedTasksIterationStrategy class
     * Strategy that can be used to iterate on all Tasks that are not included in any Composite Task.
     * It can be used for exemple propose the different tasks that can be added to a project.
     */
    class NotIncludedTasksIterationStrategy : public TasksIterationStrategy {
    protected:
        bool test(Task *tested) const override {
            if (!tested) return false;
            if (getInstance().isTaskIncluded(tested->getId())) return false;
            return true;
        }
    };

    /*!
     * \brief The ProjectValidTasksIterationStrategy class
     * This strategy can be used to list every Tasks that can be added to a project (tasks that are not
       included in any composite Task, and tasks that were not already added to a project).
     */
    class ProjectValidTasksIterationStrategy : public TasksIterationStrategy {
        bool test(Task *tested) const {
            if (!(getInstance().isTaskIncluded(tested->getId())) && ProjectFactory::getInstance().isTaskavalaible(tested))
                return true;
            else return false;
        }
    };

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
            if (!toTest) return false;
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

#endif // TASKMANAGER_H
