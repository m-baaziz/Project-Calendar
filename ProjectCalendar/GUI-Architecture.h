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
#include <QCalendarWidget>
#include <QHeaderView>

#include "TaskManager.h"
#include "Project.h"
#include "Association.h"
#include "Programmation.h"

#include "GUI-Association.h"
#include "GUI-Calendar.h"
#include "GUI-Event.h"
#include "GUI-Project.h"


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


class MainWindow : public QWidget {
    Q_OBJECT

    QVBoxLayout* mainLayer;
    QHBoxLayout* topLayer;
    QHBoxLayout* workSpaceLayer;
    QVBoxLayout* itemsMenuLayer;
    QVBoxLayout* displayLayer;
    QHBoxLayout* eventLayer;

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
    QTreeView* independentTasksTree;
    QTreeView* projectsTreeView;

    void setTasksInModel();
    void setProjectsInMenu();
    //void setEventsInMenu();
    void setIndependentTasksInMenu();
    void setProjectsTreeModel();

    // in displayLayer

    Week* calendarTable;
    QGraphicsView* treeView;
    QGraphicsScene* treeScene;

    void injectSubTaskInModel(QStandardItem* parent, Task& son);
    void injectSuccessorInModel(QStandardItem* parent, Task& son, Project& proj);
    void drawProjectTree(QModelIndex projectIndex);

    // bottom Event Layer

    EventForm* eventForm;

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

    void refreshCalendar();

public slots:
    void refreshTasksModel();
    void refreshProjectsModel();
    void refreshIndependentTasksModel();
    void refreshProjectsTreeModel();
    void showProjectsInMenu();
    void showIndependentTasksInMenu();
    void showProjectsTreeInMenu();
    void showProjectContextMenu(const QPoint& pos);
    void showTaskContextMenu(const QPoint& pos);

    void showCalendar();
};




#endif // GUIARCHITECTURE_H
