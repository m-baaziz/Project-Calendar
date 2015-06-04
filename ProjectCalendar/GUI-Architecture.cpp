#include "GUI-Architecture.h"

QStandardItemModel* MainWindow::projectsModel = new QStandardItemModel();
QStandardItemModel* MainWindow::eventsModel = new QStandardItemModel();
QStandardItemModel* MainWindow::independentTasksModel = new QStandardItemModel();


MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    this->resize(1300,800);


    mainLayer = new QVBoxLayout(this);
    topLayer = new QHBoxLayout(this);
    workSpaceLayer = new QHBoxLayout(this);
    itemsMenuLayer = new QVBoxLayout(this);
    displayLayer = new QVBoxLayout(this);

    // in topLayer

    newProjectB = new NewProjectB("New Project",this);
    newTaskB = new NewTaskB("New Task",this);
    newEventB = new QPushButton("New Event",this);
    taskTreeB = new QPushButton("Task Tree",this);
    calendarB = new QPushButton("Calendar",this);

    topLayer->addWidget(newProjectB);
    topLayer->addWidget(newTaskB);
    topLayer->addWidget(newEventB);
    topLayer->addWidget(taskTreeB);
    topLayer->addWidget(calendarB);

    // in itemsMenuLayer

    itemTypeSelector = new MyComboBox(this);
    projectsTree = new QTreeView(this);
    eventsTree = new QTreeView(this);
    independentTasksTree = new QTreeView(this);
    projectsTree->setModel(MainWindow::projectsModel);
    independentTasksTree->setModel(independentTasksModel);
    //eventsTree->setModel(eventsModel);
    projectsTree->hide();
    eventsTree->hide();

    itemTypeSelector->addItem("Projects");
    itemTypeSelector->addItem("Independent Tasks");
    //itemTypeSelector->addItem("Events");

    itemsMenuLayer->addWidget(itemTypeSelector);
    itemsMenuLayer->addWidget(projectsTree);
    itemsMenuLayer->addWidget(eventsTree);
    itemsMenuLayer->addWidget(independentTasksTree);

    //setProjectsInMenu(); // no need to call it, already done by the first "indexChanged" event on MyComboBox
    //setEventsInMenu();
    setIndependentTasksInMenu();

    // in displayLayer

    calendarTable = new QTableWidget;
    treeView = new QGraphicsView;
    treeScene = new QGraphicsScene;


    displayLayer->addWidget(calendarTable);
    displayLayer->addWidget(treeView);

    //////////////////////////////////////



    mainLayer->addLayout(topLayer);
    mainLayer->addLayout(workSpaceLayer);
    workSpaceLayer->addLayout(itemsMenuLayer,1);
    workSpaceLayer->addLayout(displayLayer,4);

    setLayout(mainLayer);
}

void MainWindow::setProjectsInMenu() {
    QStandardItem* parent = projectsModel->invisibleRootItem();
    ProjectFactory* pf = &(ProjectFactory::getInstance());
    for (Iterator<Project> it = pf->getIterator(); !(it.isDone()); it.next()) {
        QStandardItem* temp = new QStandardItem(it.current().getId());  // gonna need to manage those items, and delete them at the end of the process
        parent->appendRow(temp);
        //parent = temp;
        for(Iterator<Task> it2 = it.current().getIterator(); !(it2.isDone()); it2.next()) {
            QStandardItem* temp2 = new QStandardItem(it2.current().getId());
            temp->appendRow(temp2);
            if (it2.current().getTaskType()==COMPOSITE) {
                for (Iterator<Task> it3 = dynamic_cast<CompositeTask&>(it2.current()).getIterator(); !(it3.isDone()); it3.next()) {
                    injectSubTaskInModel(temp2,it3.current());
                }
            }
        }
    }
}

void MainWindow::setIndependentTasksInMenu() {
    QStandardItem* parent = independentTasksModel->invisibleRootItem();
    CompositeFactory::ProjectValidTasksIterationStrategy strat;
    NonPreemptiveFactory* npf = &(NonPreemptiveFactory::getInstance());
    for (Iterator<Task> it = npf->getIterator(&strat); !(it.isDone()); it.next()) {
        QStandardItem* temp = new QStandardItem(it.current().getId());
        parent->appendRow(temp);
        //parent = temp;   // this is what to do for trees -> compositions
        if (it.current().getTaskType()==COMPOSITE) {
            for (Iterator<Task> it2 = dynamic_cast<CompositeTask&>(it.current()).getIterator(); !(it2.isDone()); it2.next()) {
                injectSubTaskInModel(temp,it2.current());
            }
        }
    }
}

void MainWindow::showProjectsInMenu() {
    refreshProjectsModel();
    eventsTree->hide();
    independentTasksTree->hide();
    projectsTree->show();
}

/*void MainWindow::showEventsInMenu() {
    refreshEventsModel();
    projectsTree->hide();
    independentTasksTree->hide();
    eventsTree->show();
}*/

void MainWindow::showIndependentTasksInMenu() {
    refreshIndependentTasksModel();
    projectsTree->hide();
    independentTasksTree->show();
    eventsTree->hide();
}

void MyComboBox::handleSelectionChanged(int index){
    if (index==0) dynamic_cast<MainWindow*>(parent())->showProjectsInMenu();
    if (index==1) dynamic_cast<MainWindow*>(parent())->showIndependentTasksInMenu();

/*QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Hello !");
    msg->setText("Selected Index is :"+QString::number(index));
    msg->show();*/
}

void MainWindow::injectSubTaskInModel(QStandardItem* parent, Task& son) {
    QStandardItem* temp = new QStandardItem(son.getId());
    parent->appendRow(temp);
    if (son.getTaskType()==COMPOSITE) {
        for (Iterator<Task> it = dynamic_cast<CompositeTask&>(son).getIterator(); !(it.isDone()); it.next()) {
            injectSubTaskInModel(temp,it.current());
        }
    }
}

void MainWindow::refreshProjectsModel() {
    projectsModel->clear();
    setProjectsInMenu();
}

/*void MainWindow::refreshEventsModel() {
    eventsModel->clear();
    setEventsInMenu();
}*/

void MainWindow::refreshIndependentTasksModel() {
    independentTasksModel->clear();
    setIndependentTasksInMenu();
}

NewProjectForm::NewProjectForm(QWidget *parent) : QDialog(parent) {
    resize(300,300);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Ok,this);

    identifier = new QLineEdit(this);
    title = new QLineEdit(this);
    duration = new QTimeEdit(this);
    disponibility = new QDateEdit(this);
    deadline = new QDateEdit(this);
    tasks = new QListView(this);
    tasks->setSelectionMode(QAbstractItemView::MultiSelection);
    MainWindow* castedParent = dynamic_cast<MainWindow*>(parent);
    addTasks = new NewTaskB("New Tasks",this);


    tasks->setModel(MainWindow::independentTasksModel);

    identifierL = new QLabel("ID : ",this);
    titleL = new QLabel("title : ",this);
    durationL = new QLabel("duration : ",this);
    disponibilityL = new QLabel("disponibility : ",this);
    deadlineL = new QLabel("deadline : ",this);
    tasksL = new QLabel("Tasks : ",this);

    formLayout = new QFormLayout;
    formLayout->addRow(identifierL,identifier);
    formLayout->addRow(titleL,title);
    formLayout->addRow(durationL,duration);
    formLayout->addRow(disponibilityL,disponibility);
    formLayout->addRow(deadlineL,deadline);
    formLayout->addRow(tasksL,tasks);
    formLayout->addRow(addTasks);
    formLayout->addRow(buttonBox);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(addProject()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setLayout(formLayout);
}

void NewProjectForm::addProject() {
try {
    QString id = identifier->text();
    QString tit = title->text();
    Duration dur = Duration(duration->time().hour(),duration->time().minute());
    QDate dispo = disponibility->date();
    QDate term = deadline->date();
    MainWindow* castedParent = dynamic_cast<MainWindow*>(QWidget::window());

    NonPreemptiveFactory* npf = &(NonPreemptiveFactory::getInstance());
    ProjectFactory* pf = &(ProjectFactory::getInstance());
    Project& proj = pf->addProject(id,tit,dur,dispo,term);

    foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes())
          proj.addTask(npf->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));


    castedParent->refreshIndependentTasksModel();
    castedParent->refreshProjectsModel();
}
catch
    (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
        Project* toDelete = &(ProjectFactory::getInstance().getProject(identifier->text()));
        if (toDelete) ProjectFactory::getInstance().removeProject(toDelete);
    }

    this->destroy();
}

NewTaskB::NewTaskB(const QString& text, QWidget* parent):QPushButton(text,parent) {
    connect(this, SIGNAL(clicked()),this,SLOT(popTaskForm()));
}

void NewTaskB::popTaskForm(){
    //QDialog* form = new QDialog;
    NewTaskForm* form = new NewTaskForm(this->parentWidget());
    form->show();
}

NewTaskForm::NewTaskForm(QWidget *parent) : QDialog(parent) {
    resize(300,300);

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

    tasks->setModel(MainWindow::independentTasksModel);

    identifierL = new QLabel("ID : ",this);
    titleL = new QLabel("title : ",this);
    durationL = new QLabel("duration : ",this);
    disponibilityL = new QLabel("disponibility : ",this);
    deadlineL = new QLabel("deadline : ",this);
    taskTypeL = new QLabel("task type",this);
    tasksL = new QLabel("tasks to include : ",this);

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
try {
    QString id = identifier->text();
    QString tit = title->text();
    Duration dur = Duration(duration->time().hour(),duration->time().minute());
    QDate dispo = disponibility->date();
    QDate term = deadline->date();
    QString tatype = taskType->currentText();
    MainWindow* castedParent = dynamic_cast<MainWindow*>(this->parent());

    if (tatype == "Composite") {
        CompositeFactory* factory = &(CompositeFactory::getInstance());
        CompositeTask& ct = factory->addTask(id,tit,dur,dispo,term);
        foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes())
                ct.addSubTask(factory->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));
    }
    else {
        if (tatype == "Preemptive") {
            PreemptiveFactory* factory = &(PreemptiveFactory::getInstance());
            factory->addTask(id,tit,dur,dispo,term);
        }
        else {
            NonPreemptiveFactory* factory = &(NonPreemptiveFactory::getInstance());
            factory->addTask(id,tit,dur,dispo,term);
        }
    }

    castedParent->refreshIndependentTasksModel();
    castedParent->refreshProjectsModel();
}
catch
    (CalendarException e) {
       QMessageBox* errMessage = new QMessageBox(this);
       errMessage->setText(e.getInfo());
       errMessage->show();
       Task* toDelete = &(NonPreemptiveFactory::getInstance().getTask(identifier->text()));
       if (toDelete) NonPreemptiveFactory::getInstance().removeTask(toDelete);
  }

    this->destroy();
}
