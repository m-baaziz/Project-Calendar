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
        identifier(id), title(t), duration(dur), disponibility(dispo), deadline(term), tasktype(setTaskType()){}
    Task(const Task& t);
    Task& operator=(const Task&);
    virtual void setTaskType() = 0;

    friend class TaskManger;

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
};

class TaskManager {
    Task taches**;
    int nb;
    int max;
};

#endif // TASK_H
