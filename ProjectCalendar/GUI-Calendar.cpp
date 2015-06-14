#include "GUI-Architecture.h"
#include "GUI-Calendar.h"
#include "GUI-Event.h"

Week::Week(QWidget* parent):QWidget(parent){

    calendar = new QCalendarWidget(this);
    calendar->hide();
    week = new QTableView(this);
    week->setMinimumWidth(800);
    week->setMinimumHeight(700);
    previousWeek = new QPushButton("<<<");
    previousWeek->setMaximumWidth(200);
    nextWeek = new QPushButton(">>>");
    nextWeek->setMaximumWidth(400);
    manageWeek = new ManageWeeks(QDate::currentDate());
    manageWeek->setCalendarPopup(true);
    manageWeek->setMinimumWidth(150);

    for (unsigned int i = 0; i < 24 ; ++i){
        int hour = i;
        if (!(i % 2)) ListHours << QString("%0h00").arg(hour);
        else ListHours << QString();
    }

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(ListDays);
    model->setVerticalHeaderLabels(ListHours);

    for (int day = 0; day < 7; ++day){
        for (int halfHour = 0; halfHour < 24; ++halfHour){
            QStandardItem *item = new QStandardItem();
            model->setItem(halfHour, day, item);
            model->item(halfHour, day)->setEditable(false);
            item->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        }
    }


    QHeaderView* vHeader = week->horizontalHeader();
    vHeader->setSectionResizeMode(QHeaderView::Stretch);
    week->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    week->setModel(model);
    updateWeek();
    Hlayout1 = new QHBoxLayout;
    Hlayout1->addWidget(previousWeek, 0, Qt::AlignRight);
    Hlayout1->addWidget(manageWeek,0, Qt::AlignCenter);
    Hlayout1->addWidget(nextWeek,0, Qt::AlignLeft);

    Hlayout2 = new QHBoxLayout;
    Hlayout2->addWidget(week);

    Vlayout = new QVBoxLayout;
    Vlayout->addLayout(Hlayout1);
    Vlayout->addLayout(Hlayout2);

    this->setLayout(Vlayout);

    //Connexion des widgets
    QObject::connect(previousWeek, SIGNAL(clicked()), manageWeek, SLOT(previousWeek()));
    QObject::connect(nextWeek, SIGNAL(clicked()), manageWeek, SLOT(nextWeek()));
    QObject::connect(manageWeek, SIGNAL(dateChanged(QDate)),this, SLOT(updateWeek()));
    QObject::connect(week,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showEvents(QModelIndex)));
}

QString Week::EventsinTimeZoneToString(const QDate &d, const QTime &t, const Duration &du, QStringList* tabToFill) {
    EventsContainer temp = ProgrammationFactory::getInstance().getEventsInTimeZone(d,t,du);
    if (temp.empty()) {
        if (tabToFill) tabToFill->clear();
        return QString("");
    }
    QString toSend = QString();
    Event* event = 0;
    QTime end,endT;
    while(!(temp.empty())) {
        event = temp.front();
        temp.pop_front();
        QTime startToPrint = max(event->getTime(),t);
        end = event->getDuration()+event->getTime();
        endT = du+t;
        if (!endT.isValid()) endT = QTime(23,59,59);
        QTime endToPrint = min(end,endT);
        toSend += QString("%1 %2 - %3").arg(event->getName()).arg(startToPrint.toString("hh:mm")).arg(endToPrint.toString("hh:mm"));
        if (temp.size()>0) toSend+="\n";
        if (tabToFill) tabToFill->push_back(event->getName());
    }
    return toSend;
}

void Week::updateWeek(){
    date = manageWeek->date();

      ListDays.clear();
      ListDays<<QString("Mon %0-%1").arg(getDays(date, 1)).arg(getMonth(date,1))
              <<QString("Tue %0-%1").arg(getDays(date, 2)).arg(getMonth(date,2))
              <<QString("Wed %0-%1").arg(getDays(date, 3)).arg(getMonth(date,3))
              <<QString("Thu %0-%1").arg(getDays(date, 4)).arg(getMonth(date,4))
              <<QString("Fri %0-%1").arg(getDays(date, 5)).arg(getMonth(date,5))
              <<QString("Sat %0-%1").arg(getDays(date, 6)).arg(getMonth(date,6))
              <<QString("Sun %0-%1").arg(getDays(date, 7)).arg(getMonth(date,7));
    model->setHorizontalHeaderLabels(ListDays);

    QStringList eventsTab = QStringList();
    QVariant data;
    bool allAchieved = false;
    ProgrammationFactory* pf = &(ProgrammationFactory::getInstance());

    for (int day = 0; day < 7; ++day){
        for (int halfHour = 0; halfHour < 24; ++halfHour){
            model->item(halfHour, day)->setText(EventsinTimeZoneToString(date.addDays(day-date.dayOfWeek()+1),QTime(halfHour,0),Duration(1,0),&eventsTab));
            data = QVariant(QStringList(eventsTab));
            if(!eventsTab.empty()) {
                allAchieved = true;
                model->item(halfHour, day)->setData(QVariant(data),Qt::UserRole+2);
                for (QStringList::iterator it=eventsTab.begin(); it!=eventsTab.end(); ++it) {
                    if (!(pf->getEvent(*it)->isAchieved())) {
                        allAchieved = false;
                        break;
                    }
                }
            }
            if (allAchieved) {
                model->item(halfHour, day)->setBackground(QBrush(QColor(0,255,103)));
                allAchieved = false;
            }
            else {
                if (!(halfHour%2)) model->item(halfHour, day)->setBackground(QBrush(QColor(Qt::white)));
                else model->item(halfHour, day)->setBackground(QBrush(QColor(204,255,255)));
            }
            eventsTab.clear();
        }
    }
    week->clearSpans();

}

void ManageWeeks::previousWeek(){
    setDate(date().addDays(-7));
}

void ManageWeeks::nextWeek(){
    setDate(date().addDays(7));
}

void Week::showEvents(const QModelIndex& index) {
    QStringList temp = index.data(Qt::UserRole+2).toStringList();
    EventsInfoSet* toShow;
    if (!temp.empty()) {
        toShow = new EventsInfoSet(temp,this->parentWidget());
        toShow->show();
    }
}

