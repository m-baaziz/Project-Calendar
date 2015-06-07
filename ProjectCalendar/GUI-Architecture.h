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
#include <QPoint>
#include <QMenu>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QRegion>
#include <QRect>
#include <QPen>
#include <QPolygon>
#include <math.h>
#include <QTableView>

#include "TaskManager.h"
#include "Project.h"
#include "Association.h"


class ArrowHead : public QPolygon {

public:
    ArrowHead(int x, int y, int FX, int FY) {
        int dx = x - FX;
        int dy = y - FY;

        // normalize
        double length = sqrt(dx * dx + dy * dy);
        double unitDx = dx / length;
        double unitDy = dy / length;
        // increase this to get a larger arrow head
        const int arrowHeadBoxSize = 5;

        QPoint arrowPoint1 =  QPoint(
        (int)(x+20 - unitDx * arrowHeadBoxSize - unitDy * arrowHeadBoxSize),
        (int)(y+20 - unitDy * arrowHeadBoxSize + unitDx * arrowHeadBoxSize));
        QPoint arrowPoint2 =  QPoint(
        (int)(x+20 - unitDx * arrowHeadBoxSize + unitDy * arrowHeadBoxSize),
        (int)(y+20 - unitDy * arrowHeadBoxSize - unitDx * arrowHeadBoxSize));

        *this << QPoint(x+20,y+20) <<arrowPoint1<<arrowPoint2;

    }

};

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
    NewTaskB(const QString& text, QWidget* parent=0);
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
    void popProjectForm();
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

class CalendarTable : public QTableView {
    Q_OBJECT
public:
    CalendarTable(QWidget* parent);
public slots:

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
    QPushButton* calendarB;   // show Calendar

    // in itemsMenuLayer

    MyComboBox* itemTypeSelector;
    QTreeView* projectsTree;
    QTreeView* eventsTree;
    QTreeView* independentTasksTree;

    void setTasksInModel();
    void setProjectsInMenu();
    //void setEventsInMenu();
    void setIndependentTasksInMenu();
    void setProjectsTreeModel();

    // in displayLayer

    QTableView* calendarTable;
    QGraphicsView* treeView;
    QGraphicsScene* treeScene;

    void injectSubTaskInModel(QStandardItem* parent, Task& son);
    void injectSuccessorInModel(QStandardItem* parent, Task& son, Project& proj);
    void drawProjectTree(QModelIndex projectIndex);

    struct ProjectTreeNode {
        QModelIndex id;
        unsigned int x;
        unsigned int y;
        ProjectTreeNode(const QModelIndex& i, const unsigned int& X, const unsigned int& Y) : id(i),x(X),y(Y){}
    };
    void treeDepth(QModelIndex currentIndex, unsigned int *depth, unsigned int tempDepth);
    void drawTreeHelper(const unsigned int Y,const unsigned int X, std::vector<ProjectTreeNode>& V, QModelIndex father,unsigned int space);
public:
    MainWindow(QWidget* parent = 0);

    static QStandardItemModel* tasksModel;
    static QStandardItemModel* projectsModel;
    static QStandardItemModel* eventsModel;
    static QStandardItemModel* independentTasksModel;
    static QStandardItemModel* projectsTreeModel;

public slots:
    void refreshTasksModel();
    void refreshProjectsModel();
    void refreshIndependentTasksModel();
    void refreshProjectsTreeModel();
    //void refreshEventsModel();
    void showProjectsInMenu();
    void showIndependentTasksInMenu();
    //void showEventsInMenu();
    void showProjectContextMenu(const QPoint& pos);
    void showTaskContextMenu(const QPoint& pos);

    void showCalendar();
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

    QFormLayout* formLayout;

public:
    TaskInfo(Task* t,QWidget* parent);

};

class ProjectInfo : public QDialog {
    Q_OBJECT

    QLabel* identifier;
    QLabel* title;
    QLabel* duration;
    QLabel* disponibility;
    QLabel* deadline;
    QLabel* tasks;

    QFormLayout* formLayout;

public:
    ProjectInfo(Project* t,QWidget* parent);

};

class EditAssociationConstraint : public QDialog {
    Q_OBJECT

    QTreeView* predecessors;
    QTreeView* successors;
    Task* task;

    QPushButton* addB;
    QPushButton* removeB;
    QFormLayout* formLayout;

public :
    EditAssociationConstraint(Task* t, QWidget* parent);
public slots:
    void addAssociation();
    void removeAssociation();
};

/*class TempTree : public QTreeView {
    Q_OBJECT
public :
    TempTree(QWidget* parent) : QTreeView(parent) {
        this->setModel(MainWindow::independentTasksModel);
        QPainter* paint = new QPainter();
        QRegion* region = new QRegion(50,50,100,100);
        this->drawTree(paint,);
    }
};*/


#endif // GUIARCHITECTURE_H
