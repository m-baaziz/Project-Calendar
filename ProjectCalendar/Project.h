#ifndef PROJECT_H
#define PROJECT_H
#include "TaskManager.h"


class Project : public Aggregator<Task> {
    Project(const Project& p);
    Project& operator=(const Project& p);
protected:
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    bool isCompleted;
    TasksContainer tasks;

    void setCompleted() {isCompleted = true;}
    Project(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term) :
        identifier(id), title(t), duration(dur), disponibility(dispo), deadline(term), isCompleted(false),Aggregator<Task>(&tasks){
                if (dispo>term) throw CalendarException("Error : a Project disponibility can't come after its deadline");
            }
    virtual ~Project();
    bool isTaskAdded(Task* t); // also checks with composition ...

    friend class ProjectFactory;
public:
    QString getId() const {return identifier;}
    QString getTitle() const {return title;}
    Duration getDuration() const {return duration;}
    QDate getDisponibility() const {return disponibility;}
    QDate getDeadline() const {return deadline;}

    void setId(const QString& id) {identifier=id;}
    void setTitle(const QString& t) {title=t;}
    void setDuration(const Duration& d) {duration=d;}
    void setDisponibility(const QDate& dispo) {disponibility=dispo;}
    void setDeadline(const QDate& date) {deadline=date;}

    /*!
     * \brief addTask
     * \param t
     * This method doesn't create a task, the task has to be created previously in order to be added to a project.
     */
    Task& addTask(Task& t);
    /*!
     * \brief removeTask
     * \param id
     * This method doesn't destroy the task, it simply removes the link between the project and the task.
     */
    void removeTask(const QString& id);
};

typedef std::vector<Project*> ProjectsContainer;

class ProjectFactory : Singleton<ProjectFactory>, Aggregator<Project> {
    ProjectFactory(const ProjectFactory& pm);
    ProjectFactory& operator=(const ProjectFactory& pm);
protected:
    ProjectsContainer projects;
    ProjectFactory(): Aggregator<Project>(&projects){}
    virtual ~ProjectFactory();

    friend class Singleton<ProjectFactory>;
    friend class Handler<ProjectFactory>;
public:
    bool isTaskavalaible(Task* t) const;
    Project& addProject(const QString& id, const QString& t, const Duration& dur, const QDate& dispo, const QDate& term);
    void removeProject(Project* p);
    Project& getProject(const QString& id);
};

#endif // PROJECT_H
