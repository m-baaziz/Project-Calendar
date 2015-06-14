#ifndef GUIPROJECT_H
#define GUIPROJECT_H
#include "GUI-Task.h"

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




#endif // GUIPROJECT_H
