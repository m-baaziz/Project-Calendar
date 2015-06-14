#include "GUI-Architecture.h"
#include "GUI-Task.h"

NewTaskB::NewTaskB(const QString& text, QWidget* parent):QPushButton(text,parent) {
    connect(this, SIGNAL(clicked()),this,SLOT(popTaskForm()));
}

void NewTaskB::popTaskForm(){
    NewTaskForm* form = new NewTaskForm(this->parentWidget());
    form->show();
}



NewTaskForm::NewTaskForm(QWidget *parent) : QDialog(parent) {
    resize(300,300);
    this->setWindowTitle("Task Form");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Ok,this);

    identifier = new QLineEdit(this);
    title = new QLineEdit(this);
    duration = new QTimeEdit(this);
    disponibility = new QDateEdit(this);
    deadline = new QDateEdit(this);
    taskType = new QComboBox(this);
    tasks = new QListView(this);
    tasks->setSelectionMode(QAbstractItemView::MultiSelection);
    addTasks = new NewTaskB("New Tasks",this);
    precedes = new QListView(this);
    follows = new QListView(this);
    precedes->setSelectionMode(QAbstractItemView::MultiSelection);
    follows->setSelectionMode(QAbstractItemView::MultiSelection);

    tasks->setModel(MainWindow::independentTasksModel);
    precedes->setModel(MainWindow::tasksModel);
    follows->setModel(MainWindow::tasksModel);

    identifierL = new QLabel("ID : ",this);
    titleL = new QLabel("title : ",this);
    durationL = new QLabel("duration : ",this);
    disponibilityL = new QLabel("disponibility : ",this);
    deadlineL = new QLabel("deadline : ",this);
    taskTypeL = new QLabel("task type",this);
    tasksL = new QLabel("tasks to include : ",this);
    precedesL = new QLabel("successors",this);
    followsL = new QLabel("predecessors",this);

    taskType->addItem("Composite");
    taskType->addItem("Preemptive");
    taskType->addItem("Non-Preemptive");

    formLayout = new QFormLayout;
    formLayout->addRow(identifierL,identifier);
    formLayout->addRow(titleL,title);
    formLayout->addRow(durationL,duration);
    formLayout->addRow(disponibilityL,disponibility);
    formLayout->addRow(deadlineL,deadline);
    formLayout->addRow(taskTypeL,taskType);
    formLayout->addRow(tasksL,tasks);
    formLayout->addRow(precedesL,precedes);
    formLayout->addRow(followsL,follows);
    formLayout->addRow(addTasks);
    formLayout->addRow(buttonBox);

    connect(taskType,SIGNAL(currentIndexChanged(QString)),this,SLOT(showTasksToChoose(QString)));
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(addTask()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setLayout(formLayout);
}

void NewTaskForm::showTasksToChoose(const QString &index) {
    if (index == "Composite") {
        tasks->show();
        tasksL->show();
        addTasks->show();
    }
    else {
        tasks->hide();
        tasksL->hide();
        addTasks->hide();
    }
}


void NewTaskForm::addTask() {
    Task* newTask;
    QString temp;
    CompositeTask* ct;
try {
    QString id = identifier->text();
    QString tit = title->text();
    Duration dur = Duration(duration->time().hour(),duration->time().minute());
    QDate dispo = disponibility->date();
    QDate term = deadline->date();
    QString tatype = taskType->currentText();
    MainWindow* castedParent = dynamic_cast<MainWindow*>(this->parent());

    if (tatype == "Preemptive") {
        PreemptiveFactory* factory = &(PreemptiveFactory::getInstance());
        newTask=&(factory->addTask(id,tit,dur,dispo,term));
    }
    else if (tatype == "Non-Preemptive") {
        NonPreemptiveFactory* factory = &(NonPreemptiveFactory::getInstance());
        newTask=&(factory->addTask(id,tit,dur,dispo,term));
    }
    else if (tatype == "Composite") {
        CompositeFactory* factory = &(CompositeFactory::getInstance());
        ct = &(factory->addTask(id,tit,dur,dispo,term));
        newTask = ct;
    }
        temp = identifier->text();
    NonPreemptiveFactory* factory = &(NonPreemptiveFactory::getInstance());
    AssociationManager* am = &(AssociationManager::getInstance());
    foreach (const QModelIndex &index,precedes->selectionModel()->selectedIndexes()) {
        am->addAssociation(newTask,&(factory->getTask(MainWindow::tasksModel->itemFromIndex(index)->text())));
    }
    foreach (const QModelIndex &index,follows->selectionModel()->selectedIndexes()) {
        am->addAssociation(&(factory->getTask(MainWindow::tasksModel->itemFromIndex(index)->text())),newTask);
    }

    if (tatype=="Composite") {
        foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes()) // we do this to make sure that we add sub tasks into the composte task only if we are sure that the new task is valid.
             ct->isValidSubTask(factory->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));
        foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes())
             ct->addSubTask(factory->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));
    }
    castedParent->refreshIndependentTasksModel();
    castedParent->refreshProjectsModel();
    this->destroy();
}
catch
    (CalendarException e) {
        Task* toDelete;
        if (NonPreemptiveFactory::getInstance().isTaskHere(temp)) {
            toDelete = &(NonPreemptiveFactory::getInstance().getTask(temp));
            NonPreemptiveFactory::getInstance().removeTask(toDelete);
        }
       QMessageBox* errMessage = new QMessageBox(this);
       errMessage->setText(e.getInfo());
       errMessage->show();
  }

}

AddTaskForm::AddTaskForm(QWidget *parent) : QDialog(parent) {
    resize(300,300);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Ok,this);

    tasks = new QListView(this);
    tasks->setSelectionMode(QAbstractItemView::MultiSelection);
    tasks->setModel(MainWindow::independentTasksModel);
    tasksL = new QLabel("tasks to add : ",this);
    addTasks = new NewTaskB("New Tasks",this);

    formLayout = new QFormLayout(this);
    formLayout->addRow(tasksL,tasks);
    formLayout->addRow(addTasks);
    formLayout->addRow(buttonBox);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(addTask()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setLayout(formLayout);
}

void AddTaskToProjectForm::addTask() {
    NonPreemptiveFactory* tFactory = &(NonPreemptiveFactory::getInstance());
    //Project& proj = //on prend le project selectionnée par le clic droit
    try {
        foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes())
                project->addTask(tFactory->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));
        MainWindow* castedParent = dynamic_cast<MainWindow*>(QWidget::window());
        castedParent->refreshIndependentTasksModel();
        castedParent->refreshProjectsModel();
        this->destroy();
    }
    catch (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
    }
}

void AddTaskToCompositeTaskForm::addTask() {
    CompositeFactory* factory = &(CompositeFactory::getInstance());
    //CompositeTask& ct = //on prend la composite Task selectionnée par le clic droit
    try {
        foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes())
                compoTask->addSubTask(factory->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));
        MainWindow* castedParent = dynamic_cast<MainWindow*>(QWidget::window());
        castedParent->refreshIndependentTasksModel();
        castedParent->refreshProjectsModel();
        this->destroy();
    }
    catch (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
    }
}

TaskInfo::TaskInfo(Task *t, QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Task "+t->getId());

    QString temp = "";
    identifier = new QLabel(t->getId(),this);
    title = new QLabel(t->getTitle(),this);
    duration = new QLabel(t->getDuration().toString(),this);
    disponibility = new QLabel(t->getDisponibility().toString(),this);
    deadline = new QLabel(t->getDeadline().toString(),this);
    if (t->getTaskType()==COMPOSITE) {
        temp = "";
        for (TasksIterator it = dynamic_cast<CompositeTask*>(t)->getIterator(); !(it.isDone()); it.next()) {
            temp += " "+it.current().getId();
        }
        tasks = new QLabel(temp,this);
    }
    if (t->getTaskType()==COMPOSITE) taskType = new QLabel("composite",this);
    if (t->getTaskType()==UNITARY) {
        taskType = new QLabel("unitary",this);
        UnitaryTask* tempTask = dynamic_cast<UnitaryTask*>(t);
        if (tempTask->isPreemptive()) subType = new QLabel("preemptive",this);
        if (!(tempTask->isPreemptive())) subType = new QLabel("non preemptive",this);

        QString progStr = "";
        ProgrammationFactory::SpecificEventsContainer progs = ProgrammationFactory::getInstance().getProgrammations(tempTask);
        Programmation* tempProg;
        for (ProgrammationFactory::SpecificEventsContainer::iterator it = progs.begin(); it!=progs.end(); ++it) {
            tempProg = *it;
            progStr+=QString("%0 from %1 to %2 \n").arg(tempProg->getDate().toString()).arg(tempProg->getTime().toString("hh:mm")).arg((tempProg->getDuration()+tempProg->getTime()).toString("hh:mm"));
        }
        programmations = new QLabel(progStr);               // display programmations
    }
    TasksContainer predecessors = AssociationManager::getInstance().getTaskPredecessors(t);
    TasksContainer successors = AssociationManager::getInstance().getTaskSuccessors(t);
    temp = "";
    for (TasksContainer::iterator it = predecessors.begin(); it != predecessors.end(); ++it) {
        if (!(t->getTaskType()==COMPOSITE && dynamic_cast<CompositeTask*>(t)->isSubTaskHere((*it)->getId())))  // We don't want to display implicit precedence of composite tasks (follows its subtasks)
            temp += " "+(*it)->getId();
    }
    follows = new QLabel(temp,this);
    temp = "";
    for (TasksContainer::iterator it = successors.begin(); it != successors.end(); ++it) {
        if (!((*it)->getTaskType()==COMPOSITE && dynamic_cast<CompositeTask*>(*it)->isSubTaskHere(t->getId())))
            temp += " "+(*it)->getId();
    }
    precedes = new QLabel(temp,this);

    formLayout = new QFormLayout(this);

    formLayout->addRow("id : ",identifier);
    formLayout->addRow("title : ",title);
    formLayout->addRow("duration",duration);
    formLayout->addRow("disponibility",disponibility);
    formLayout->addRow("deadline",deadline);
    if(t->getTaskType()==COMPOSITE) formLayout->addRow("sub-tasks : ",tasks);
    formLayout->addRow("task type : ",taskType);
    if (t->getTaskType()==UNITARY) formLayout->addRow("sub type : ",subType);
    formLayout->addRow("predecessors : ",follows);
    formLayout->addRow("successors",precedes);
    if(t->getTaskType()==UNITARY)formLayout->addRow("programmation(s) : ",programmations);

    setLayout(formLayout);
}
