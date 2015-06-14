#ifndef GUIEVENT_H
#define GUIEVENT_H
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
#include <QVariant>

#include "Event.h"
#include "Programmation.h"


class EventForm : public QWidget {
    Q_OBJECT

    QComboBox* EventTypeSelector;
    QLineEdit* name;
    QDateEdit* date;
    QTimeEdit* time;
    QTimeEdit* duration;
    QLineEdit* place;
    QLineEdit* participants;
    QLineEdit* task;
    QComboBox* type;
    QDialogButtonBox* buttonBox;

    QLabel* nameL;
    QLabel* dateL;
    QLabel* timeL;
    QLabel* durationL;
    QLabel* placeL;
    QLabel* participantsL;
    QLabel* taskL;
    QLabel* typeL;

    QHBoxLayout* formLayout;
    QVBoxLayout* part1;
    QVBoxLayout* part2;
    QHBoxLayout* V1;
    QHBoxLayout* V2;
    QFormLayout* F1;
    QFormLayout* F2;
    QFormLayout* F3;
    QFormLayout* F4;
public:
    EventForm(QWidget* parent);

    void addProgrammation();
    void addActivity();
public slots:
    void addElement();
    void handleSelectionChanged(int index);
};

class EventInfoElement : public QWidget {
    Q_OBJECT

    Event* target;

    QLabel* name;
    QLabel* place;
    QLabel* timeInfos;
    QLabel* type;
    QLabel* task;
    QLabel* participants;
    QPushButton* achieveB;
    QPushButton* removeB;

    QVBoxLayout* mainLayer;
    QHBoxLayout* H1;
    QHBoxLayout* H2;
    QHBoxLayout* H3;
    QHBoxLayout* H4;
    QHBoxLayout* H5;
    QHBoxLayout* H6;
public:
    EventInfoElement(Event *e, QWidget* parent = 0);
public slots:
    void achieveEvent();
    void removeEvent();
};

class EventsInfoSet : public QDialog {
    Q_OBJECT
    QVBoxLayout* mainLayer;
    std::vector<EventInfoElement*> infoSet;

public :
    EventsInfoSet(const QStringList& eventsList, QWidget* parent = 0);
};

#endif // GUIEVENT_H
