#ifndef GUICALENDAR_H
#define GUICALENDAR_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableWidget>
#include <QFormLayout>
#include <QTimeEdit>
#include <QDateEdit>
#include <QTableView>
#include <QCalendarWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QDialogButtonBox>

#include "Calendar.h"


class ManageWeeks : public QDateEdit{
    Q_OBJECT
public slots:
    void nextWeek();
    void previousWeek();
public:
    ManageWeeks(const QDate& date, QDateEdit* parent=0) : QDateEdit(date,parent){}
};

class Week : public QWidget{

    Q_OBJECT

private:
    QDate date;
    QStringList ListDays, ListHours;
    QTableView* week;
    QCalendarWidget* calendar;
    ManageWeeks* manageWeek;
    QStandardItemModel* model;
    QHBoxLayout *Hlayout1, *Hlayout2;
    QVBoxLayout* Vlayout;
    QPushButton *nextWeek, *previousWeek;
    QLabel *currentWeek;

    /*!
     * \brief EventsinTimeZoneToString
     * \param d
     * \param t
     * \param du
     * \param tabToFill
     * \return
     * This method returns a string displaying all events in a given Time Zone (displays name, start time and end time)
       It is possible to give a pointer of QStringList to fill it with the several event names.
     */
    QString EventsinTimeZoneToString(const QDate& d, const QTime& t, const Duration& du, QStringList* tabToFill=0);

public:
    Week(QWidget* parent=0);
    int getDays(QDate& date, int j){return date.addDays(-date.dayOfWeek()+j).day();}
    int getMonth(QDate& date, int j){return date.addDays(-date.dayOfWeek()+j).month();}

public slots:
    void updateWeek();
    void showEvents(const QModelIndex& index);
};


#endif // GUICALENDAR_H
