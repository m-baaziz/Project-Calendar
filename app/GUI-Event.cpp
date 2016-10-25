#include "GUI-Architecture.h"
#include "GUI-Event.h"

EventForm::EventForm(QWidget *parent) : QWidget(parent) {
    EventTypeSelector = new QComboBox(this);
    EventTypeSelector->addItem("Activity");
    EventTypeSelector->addItem("Task Programmation");
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok,this);
    EventTypeSelector->connect(EventTypeSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(handleSelectionChanged(int)));

    name = new QLineEdit();
    date = new QDateEdit();
    time = new QTimeEdit();
    duration = new QTimeEdit();
    place = new QLineEdit();
    participants = new QLineEdit();
    task = new QLineEdit();
    task->hide();
    type = new QComboBox();

    for (QStringList::iterator it = activityTypeTable.begin(); it!=activityTypeTable.end(); ++it) {
        type->addItem(*it);
    }

    nameL = new QLabel("name : ");
    dateL = new QLabel("date : ");
    timeL = new QLabel("time : ");
    durationL = new QLabel("duration : ");
    placeL = new QLabel("place : ");
    participantsL = new QLabel("participants : \n(seperated by ',') ");
    taskL = new QLabel("task : ");
    taskL->hide();
    typeL = new QLabel("type : ");

    formLayout = new QHBoxLayout();
    part1 = new QVBoxLayout();
    part2 = new QVBoxLayout();
    V1 = new QHBoxLayout();
    V2 = new QHBoxLayout();
    F1 = new QFormLayout();
    F2 = new QFormLayout();
    F3 = new QFormLayout();
    F4 = new QFormLayout();

    F1->addRow(nameL,name);
    F1->addRow(placeL,place);
    F2->addRow(dateL,date);
    F2->addRow(timeL,time);
    F2->addRow(durationL,duration);
    F3->addRow(typeL,type);
    F3->addRow(taskL,task);
    F3->addRow(participantsL,participants);
    F4->addRow(EventTypeSelector);
    F4->addRow(buttonBox);

    formLayout->addLayout(F1,2);
    formLayout->addLayout(F2,2);
    formLayout->addLayout(F3,2);
    formLayout->addLayout(F4,1);

    setLayout(formLayout);

    QObject::connect(buttonBox,SIGNAL(accepted()),SLOT(addElement()));

}

void EventForm::handleSelectionChanged(int index){
    if (index==0) {
        taskL->hide();
        task->hide();
        typeL->show();
        type->show();
    }
    if (index==1) {
        typeL->hide();
        type->hide();
        taskL->show();
        task->show();
    }
}

void EventForm::addProgrammation() {
    ProgrammationFactory* pf;
    try {
        pf = &(ProgrammationFactory::getInstance());
        UnitaryTask* target = &(NonPreemptiveFactory::getInstance().getTypedTask(task->text()));
        Duration taskDuration = Duration(duration->time().hour(),duration->time().minute());
        ParticipantsContainer eventParticipants = participants->text().split(",");
        pf->scheduleTask(target,name->text(),date->date(),time->time(),taskDuration,place->text(),eventParticipants);

        QMessageBox* succMessage = new QMessageBox(this);
        succMessage->setText("Task "+target->getId()+" successfully scheduled");
        succMessage->show();
    }
    catch (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
    }
    catch (TasksContainer toSchedule) {
        QString toPrint = "";
        TasksContainer::iterator beforeLast = --(toSchedule.end()); // in order not to add ' , ' after the last task
        for (TasksContainer::iterator it = toSchedule.begin(); it!=beforeLast; ++it) {
            toPrint += (*it)->getId()+", ";
        }
        if (toSchedule.size()>0)toPrint += toSchedule.back()->getId();
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText("Error : Pleas respect precedence constraints, you need to schedule "+toPrint+" before beeing able to schedule "+task->text());
        errMessage->show();
    }
}

void EventForm::addElement() {
    if (!(task->isHidden())) {
        addProgrammation();
    }
    if (!(type->isHidden())) {
        addActivity();
    }
    name->setText("");
    date->setDate(QDate());
    time->setTime(QTime());
    duration->setTime(QTime());
    place->setText("");
    type->setCurrentIndex(0);
    participants->setText("");
    task->setText("");
    dynamic_cast<MainWindow*>(QWidget::window())->refreshCalendar();
}

void EventForm::addActivity() {
    ActivityFactory* af;
    try {
        af = &(ActivityFactory::getInstance());
        Duration activityDuration = Duration(duration->time().hour(),duration->time().minute());
        ParticipantsContainer eventParticipants = participants->text().split(",");
        af->addActivity(name->text(),date->date(),time->time(),activityDuration,place->text(),getActivityType(type->currentText()),eventParticipants);

        QMessageBox* succMessage = new QMessageBox(this);
        succMessage->setText("Activity "+name->text()+" successfully scheduled");
        succMessage->show();
    }
    catch (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
    }
}

EventInfoElement::EventInfoElement(Event *e, QWidget *parent) : target(e), QWidget(parent) {
    name = new QLabel(e->getName());
    place = new QLabel("place : "+e->getPlace());
    timeInfos = new QLabel(QString("%0 at %1, duration : %2").arg(e->getDate().toString()).arg(e->getTime().toString("hh:mm")).arg(e->getDuration().toString()));
    type = new QLabel();
    task = new QLabel();
    const Activity* act = dynamic_cast<const Activity*>(e);
    const Programmation* prog = dynamic_cast<const Programmation*>(e);
    if (act) {
        task->hide();
        type->setText("Activity Type : "+activityTypeTable[act->getActivityType()]);
        type->show();
    }
    if (prog) {
        type->hide();
        task->setText("Target Task : "+prog->getTask()->getId());
        task->show();
    }
    participants = new QLabel("Participants : "+e->getParticipants().join(","));

    achieveB = new QPushButton("Achieve");
    removeB = new QPushButton("Remove");
    if (e->isAchieved()) {
        achieveB->hide();
        removeB->hide();
    }

    QObject::connect(achieveB,SIGNAL(clicked()),this,SLOT(achieveEvent()));
    QObject::connect(removeB,SIGNAL(clicked()),this,SLOT(removeEvent()));

    // define and connect achieve and remove buttons

    mainLayer = new QVBoxLayout();
    H1 = new QHBoxLayout();
    H2 = new QHBoxLayout();
    H3 = new QHBoxLayout();
    H4 = new QHBoxLayout();
    H5= new QHBoxLayout();
    H6 = new QHBoxLayout();

    H1->addWidget(name);
    H2->addWidget(timeInfos);
    H3->addWidget(type);
    H3->addWidget(task);
    H4->addWidget(place);
    H5->addWidget(participants);
    H6->addWidget(achieveB);
    H6->addWidget(removeB);
    mainLayer->addLayout(H1);
    mainLayer->addLayout(H2);
    mainLayer->addLayout(H3);
    mainLayer->addLayout(H4);
    mainLayer->addLayout(H5);
    mainLayer->addLayout(H6);
    mainLayer->addWidget(new QLabel("--------------------------------------------------------------------"));

    setLayout(mainLayer);
}

void EventInfoElement::achieveEvent() {
    try {
        if (target->getEventType() == PROGRAMMATION)
            ProgrammationFactory::getInstance().achieveEvent(target->getName());
        else if (target->getEventType() == ACTIVITY)
                ActivityFactory::getInstance().achieveEvent(target->getName());
        achieveB->hide();
        removeB->hide();
    }
    catch (CalendarException e) {
        QMessageBox* error = new QMessageBox();
        error->setText(e.getInfo());
        error->show();
    }
}

void EventInfoElement::removeEvent() {
    try {
        ProgrammationFactory::getInstance().removeEvent(target->getName());
        this->hide();
    }
    catch (CalendarException e) {
        QMessageBox* error = new QMessageBox();
        error->setText(e.getInfo());
        error->show();
    }
}

EventsInfoSet::EventsInfoSet(const QStringList &eventsList, QWidget *parent) : QDialog(parent) {
    mainLayer = new QVBoxLayout(this);

    ProgrammationFactory* pf = &(ProgrammationFactory::getInstance());
    for (QStringList::const_iterator it=eventsList.begin(); it!=eventsList.end(); ++it) {
        try {
            infoSet.push_back(new EventInfoElement(pf->getEvent(*it),this));
            mainLayer->addWidget(infoSet.back());
        }
        catch (CalendarException e) {
            QMessageBox* error = new QMessageBox();
            error->setText(e.getInfo());
            mainLayer->addWidget(error);
        }
    }
    setLayout(mainLayer);
}
