#ifndef GUITASK_H
#define GUITASK_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeView>
#include <QGraphicsView>
#include <QDialog>
#include <QFormLayout>
#include <QTimeEdit>
#include <QDateEdit>
#include <QMessageBox>
#include <QListWidget>
#include <QListView>
#include <QDialogButtonBox>
#include <QPoint>
#include <QMenu>

#include "Project.h"


class NewTaskB : public QPushButton {
    Q_OBJECT
public:
    NewTaskB(const QString& text, QWidget* parent=0);
public slots:
    void popTaskForm();
};



class NewTaskForm : public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;

    QLineEdit* identifier;
    QLineEdit* title;
    QTimeEdit* duration;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QComboBox* taskType;
    QListView* tasks;
    NewTaskB* addTasks;
    QListView* precedes;
    QListView* follows;

    QLabel* identifierL;
    QLabel* titleL;
    QLabel* durationL;
    QLabel* disponibilityL;
    QLabel* deadlineL;
    QLabel* tasksL;
    QLabel* taskTypeL;
    QLabel* precedesL;
    QLabel* followsL;

    QFormLayout* formLayout;

public:
    NewTaskForm(QWidget* parent = 0);
public slots:
    void addTask();
    void showTasksToChoose(const QString& index);
};

/*!
 * \brief The AddTaskForm class
 * Form used to add Tasks to Projects and Composite Tasks.
 */
class AddTaskForm : public QDialog {
protected:
    Q_OBJECT
    QDialogButtonBox* buttonBox;
    NewTaskB* addTasks;
    QLabel* tasksL;
    QFormLayout* formLayout;
public:
    QListView* tasks;
    AddTaskForm(QWidget* parent=0);
    virtual ~AddTaskForm(){}
public slots:
    virtual void addTask()=0;
};


class AddTaskToProjectForm : public AddTaskForm {
    Q_OBJECT
    Project* project;
public:
    AddTaskToProjectForm(Project* proj,QWidget* parent=0) : project(proj),AddTaskForm(parent) {
        setWindowTitle("Add Task to Project");
    }
public slots:
    void addTask() override;
};

class AddTaskToCompositeTaskForm : public AddTaskForm {
    Q_OBJECT
    CompositeTask* compoTask;
public:
    AddTaskToCompositeTaskForm(CompositeTask* task,QWidget* parent) : compoTask(task),AddTaskForm(parent){
        this->setWindowTitle("Add Task to Composite Task");
    }
public slots:
    void addTask() override;
};

class TaskInfo : public QDialog {
    Q_OBJECT

    QLabel* identifier;
    QLabel* title;
    QLabel* duration;
    QLabel* disponibility;
    QLabel* deadline;
    QLabel* tasks;
    QLabel* taskType;
    QLabel* subType;
    QLabel* precedes;
    QLabel* follows;
    QLabel* programmations;

    QFormLayout* formLayout;

public:
    TaskInfo(Task* t,QWidget* parent);

};


#endif // GUITASK_H
