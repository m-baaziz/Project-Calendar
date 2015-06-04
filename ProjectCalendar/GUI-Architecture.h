#ifndef GUIARCHITECTURE_H
#define GUIARCHITECTURE_H
#include <QApplication>
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
#include <QTableWidget>
#include <QGraphicsView>
#include <QDialog>
#include <QFormLayout>
#include <QTimeEdit>
#include <QDateEdit>
#include <QMessageBox>
#include <QListWidget>
#include <QListView>
#include <QDialogButtonBox>

#include "TaskManager.h"
#include "Project.h"
#include "Association.h"


class MyComboBox: public QComboBox {
  Q_OBJECT
public:
    MyComboBox(QWidget* parent=0):QComboBox(parent){
      this->setParent(parent);
      connect(this , SIGNAL(currentIndexChanged(int)),this,SLOT(handleSelectionChanged(int)));
    };
    ~ MyComboBox(){}

public slots:
    void handleSelectionChanged(int index);
};

class NewTaskB : public QPushButton {
    Q_OBJECT
public:
    NewTaskB(const QString& text, QWidget* parent=0):QPushButton(text,parent) {
        connect(this, SIGNAL(clicked()),this,SLOT(popTaskForm()));
    }
public slots:
    void popTaskForm();
};

class NewProjectForm : public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;
    QLineEdit* identifier;
    QLineEdit* title;
    QTimeEdit* duration;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QListView* tasks;
    NewTaskB* addTasks;

    QLabel* identifierL;
    QLabel* titleL;
    QLabel* durationL;
    QLabel* disponibilityL;
    QLabel* deadlineL;
    QLabel* tasksL;

    QFormLayout* formLayout;

public:
    NewProjectForm(QWidget* parent = 0);
public slots:
    void addProject();

};

class NewProjectB : public QPushButton {
    Q_OBJECT
public:
    NewProjectB(const QString& text, QWidget* parent=0):QPushButton(text,parent) {
        connect(this, SIGNAL(clicked()),this,SLOT(popProjectForm()));
    }
public slots:
    void popProjectForm(){
        NewProjectForm* form = new NewProjectForm(this->parentWidget());
        form->show();
    }
};

class NewTaskForm : public QDialog {
    Q_OBJECT
    QDialogButtonBox* buttonBox;
    QStandardItemModel* tempi;

    QLineEdit* identifier;
    QLineEdit* title;
    QTimeEdit* duration;
    QDateEdit* disponibility;
    QDateEdit* deadline;
    QComboBox* taskType;
    QListView* tasks;

    QLabel* identifierL;
    QLabel* titleL;
    QLabel* durationL;
    QLabel* disponibilityL;
    QLabel* deadlineL;
    QLabel* tasksL;
    QLabel* taskTypeL;

    QFormLayout* formLayout;

public:
    NewTaskForm(QWidget* parent = 0);
public slots:
    void addTask();
    void showTasksToChoose(const QString& index);
};


class MainWindow : public QWidget {
    Q_OBJECT
    QVBoxLayout* mainLayer;
    QHBoxLayout* topLayer;
    QHBoxLayout* workSpaceLayer;
    QVBoxLayout* itemsMenuLayer;
    QVBoxLayout* displayLayer;

    // in topLayer

    /*!
     * \brief xxxxxxB
     * These are the top layer buttons to perform the main actions.
     * B stands for Button.
     */
    NewProjectB* newProjectB;
    QPushButton* newTaskB;
    QPushButton* newEventB;
    QPushButton* taskTreeB;   // show task tree
    QPushButton* calendarB;   // show Calendar

    // in itemsMenuLayer

    MyComboBox* itemTypeSelector;
    QTreeView* projectsTree;
    QTreeView* eventsTree;
    QTreeView* independentTasksTree;


    void setProjectsInMenu();
    //void setEventsInMenu();
    void setIndependentTasksInMenu();

    // in displayLayer

    QTableWidget* calendarTable;
    QGraphicsView* treeView;
    QGraphicsScene* treeScene;

    void injectSubTaskInModel(QStandardItem* parent, Task& son);

public:
    MainWindow(QWidget* parent = 0);

    QStandardItemModel* projectsModel;
    QStandardItemModel* eventsModel;
    QStandardItemModel* independentTasksModel;

public slots:
    void refreshProjectsModel();
    void refreshIndependentTasksModel();
    //void refreshEventsModel();
    void showProjectsInMenu();
    void showIndependentTasksInMenu();
    //void showEventsInMenu();
};

#endif // GUIARCHITECTURE_H
