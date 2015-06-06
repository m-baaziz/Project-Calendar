#include "GUI-Architecture.h"

QStandardItemModel* MainWindow::tasksModel = new QStandardItemModel();
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
    independentTasksTree->hide();
    eventsTree->hide();
    projectsTree->hide();

    projectsTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(projectsTree, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showProjectContextMenu(const QPoint&)));

    independentTasksTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(independentTasksTree, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showTaskContextMenu(const QPoint&)));

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
    setTasksInModel();

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

void MainWindow::setTasksInModel() {
    QStandardItem* parent = tasksModel->invisibleRootItem();
    NonPreemptiveFactory* npf = &(NonPreemptiveFactory::getInstance());
    for (Iterator<Task> it = npf->getIterator(); !(it.isDone()); it.next()) {
        QStandardItem* temp = new QStandardItem(it.current().getId());
        temp->setFlags(temp->flags() & ~Qt::ItemIsEditable);
        parent->appendRow(temp);
        if (it.current().getTaskType()==COMPOSITE) {
            for (Iterator<Task> it2 = dynamic_cast<CompositeTask&>(it.current()).getIterator(); !(it2.isDone()); it2.next()) {
                injectSubTaskInModel(temp,it2.current());
            }
        }
    }
}

void MainWindow::setProjectsInMenu() {
    QStandardItem* parent = projectsModel->invisibleRootItem();
    ProjectFactory* pf = &(ProjectFactory::getInstance());
    for (Iterator<Project> it = pf->getIterator(); !(it.isDone()); it.next()) {
        QStandardItem* temp = new QStandardItem(it.current().getId());  // gonna need to manage those items, and delete them at the end of the process
        temp->setFlags(temp->flags() & ~Qt::ItemIsEditable);
        parent->appendRow(temp);
        //parent = temp;
        for(Iterator<Task> it2 = it.current().getIterator(); !(it2.isDone()); it2.next()) {
            QStandardItem* temp2 = new QStandardItem(it2.current().getId());
            temp2->setFlags(temp2->flags() & ~Qt::ItemIsEditable);
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
        temp->setFlags(temp->flags() & ~Qt::ItemIsEditable);
        parent->appendRow(temp);
        //parent = temp;   // this is what to do for trees -> compositions
        if (it.current().getTaskType()==COMPOSITE) {
            for (Iterator<Task> it2 = dynamic_cast<CompositeTask&>(it.current()).getIterator(); !(it2.isDone()); it2.next()) {
                injectSubTaskInModel(temp,it2.current());
            }
        }
    }
}

void MainWindow::injectSubTaskInModel(QStandardItem* parent, Task& son) {
    QStandardItem* temp = new QStandardItem(son.getId());
    temp->setFlags(temp->flags() & ~Qt::ItemIsEditable);
    parent->appendRow(temp);
    if (son.getTaskType()==COMPOSITE) {
        for (Iterator<Task> it = dynamic_cast<CompositeTask&>(son).getIterator(); !(it.isDone()); it.next()) {
            injectSubTaskInModel(temp,it.current());
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

void MainWindow::showProjectContextMenu(const QPoint &pos) {
    QPoint globalPos = projectsTree->mapToGlobal(pos);
    QMenu* menu = new QMenu(this);
    Project* proj;
    Task* t;
    QString selectedProject = projectsTree->indexAt(pos).data(Qt::DisplayRole).toString();
    try {
        proj = &(ProjectFactory::getInstance().getProject(selectedProject));
        menu->addAction("add tasks");
        //menu->addAction("edit");
        menu->addAction("remove");
        menu->addAction("infos");

        QAction* selectedItem = menu->exec(globalPos);
        if (selectedItem && selectedItem->text()=="add tasks") {
            AddTaskToProjectForm* form = new AddTaskToProjectForm(proj,this);
            form->show();
        }
        if (selectedItem && selectedItem->text()=="remove") {
            ProjectFactory::getInstance().removeProject(proj);
            refreshProjectsModel();
            refreshIndependentTasksModel();
        }
        if (selectedItem && selectedItem->text()=="infos") {
            ProjectInfo* projectinfo = new ProjectInfo(proj,this);
            projectinfo->show();
        }
    }
    catch (CalendarException e) {


    QString selectedTask = projectsTree->indexAt(pos).data(Qt::DisplayRole).toString();
    try {
        t = &(NonPreemptiveFactory::getInstance().getTask(selectedTask));
        if (t->getTaskType()==COMPOSITE) menu->addAction("add subtasks");
        else {
            UnitaryTask* ut = &(NonPreemptiveFactory::getInstance().getTypedTask(selectedTask));
            menu->addAction("schedule programmation");
        }
        //menu->addAction("edit");
        menu->addAction("remove");
        menu->addAction("infos");

        QAction* selectedItem = menu->exec(globalPos);
        if (selectedItem && selectedItem->text()=="add subtasks") {
            AddTaskToCompositeTaskForm* form = new AddTaskToCompositeTaskForm(dynamic_cast<CompositeTask*>(t),this);
            form->show();
        }
        if (selectedItem && selectedItem->text()=="remove") {
            NonPreemptiveFactory::getInstance().removeTask(t);
            refreshProjectsModel();
            refreshIndependentTasksModel();
        }
        if (selectedItem && selectedItem->text()=="infos") {
            TaskInfo* taskinfo = new TaskInfo(t,this);
            taskinfo->show();
        }
    }
    catch (CalendarException e) {return;}
    }

}

void MainWindow::showTaskContextMenu(const QPoint &pos) {
    QPoint globalPos = independentTasksTree->mapToGlobal(pos);
    QMenu* menu = new QMenu(this);
    Task* t;
    QString selectedTask = independentTasksTree->indexAt(pos).data(Qt::DisplayRole).toString();
    try {
        t = &(NonPreemptiveFactory::getInstance().getTask(selectedTask));
        if (t->getTaskType()==COMPOSITE) menu->addAction("add subtasks");
        else {
            UnitaryTask* ut = &(NonPreemptiveFactory::getInstance().getTypedTask(selectedTask));
            menu->addAction("schedule programmation");
        }
        //menu->addAction("edit");
        menu->addAction("remove");
        menu->addAction("infos");
    }
    catch (CalendarException e) {return;}
    QAction* selectedItem = menu->exec(globalPos);

    if (selectedItem && selectedItem->text()=="add subtasks") {
        AddTaskToCompositeTaskForm* form = new AddTaskToCompositeTaskForm(dynamic_cast<CompositeTask*>(t),this);
        form->show();
    }
    if (selectedItem && selectedItem->text()=="remove") {
        NonPreemptiveFactory::getInstance().removeTask(t);
        refreshProjectsModel();
        refreshIndependentTasksModel();
    }
    if (selectedItem && selectedItem->text()=="infos") {
        TaskInfo* taskinfo = new TaskInfo(t,this);
        taskinfo->show();
    }
}

void MyComboBox::handleSelectionChanged(int index){
    if (index==0) dynamic_cast<MainWindow*>(parent())->showProjectsInMenu();
    if (index==1) dynamic_cast<MainWindow*>(parent())->showIndependentTasksInMenu();
}


void MainWindow::refreshProjectsModel() {
    MainWindow::projectsModel->clear();
    setProjectsInMenu();
    refreshTasksModel();
}

/*void MainWindow::refreshEventsModel() {
    eventsModel->clear();
    setEventsInMenu();
}*/

void MainWindow::refreshIndependentTasksModel() {
    independentTasksModel->clear();
    setIndependentTasksInMenu();
    refreshTasksModel();
}

void MainWindow::refreshTasksModel() {
    tasksModel->clear();
    setTasksInModel();
}

NewProjectForm::NewProjectForm(QWidget *parent) : QDialog(parent) {
    resize(300,300);
    this->setWindowTitle("Project Form");

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

    foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes()) // we do this to make sure that we add tasks to the project only if the new proeject is valid (in order not to delete the tasks when we would delete the wrong project).
          proj.isTaskValidForProject(npf->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));

    foreach (const QModelIndex &index,tasks->selectionModel()->selectedIndexes())
          proj.addTask(npf->getTask(MainWindow::independentTasksModel->itemFromIndex(index)->text()));


    castedParent->refreshIndependentTasksModel();
    castedParent->refreshProjectsModel();
    this->destroy();
}
catch
    (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
        Project* toDelete = &(ProjectFactory::getInstance().getProject(identifier->text()));
        if (toDelete) ProjectFactory::getInstance().removeProject(toDelete);
    }
}

NewTaskB::NewTaskB(const QString& text, QWidget* parent):QPushButton(text,parent) {
    connect(this, SIGNAL(clicked()),this,SLOT(popTaskForm()));
}

void NewTaskB::popTaskForm(){
    //QDialog* form = new QDialog;
    NewTaskForm* form = new NewTaskForm(this->parentWidget());
    form->show();
}

void NewProjectB::popProjectForm(){
    NewProjectForm* form = new NewProjectForm(this->parentWidget());
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
    duration = new QLabel(QString::number(t->getDuration().getHours())+"H"+QString::number(t->getDuration().getMinutes()),this);
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
    }
    TasksContainer predecessors = AssociationManager::getInstance().getTaskPredecessors(t);
    TasksContainer successors = AssociationManager::getInstance().getTaskSuccessors(t);
    temp = "";
    for (TasksContainer::iterator it = predecessors.begin(); it != predecessors.end(); ++it)
        temp += " "+(*it)->getId();
    follows = new QLabel(temp,this);
    temp = "";
    for (TasksContainer::iterator it = successors.begin(); it != successors.end(); ++it)
        temp += " "+(*it)->getId();
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

    setLayout(formLayout);
}

ProjectInfo::ProjectInfo(Project *t, QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Project "+t->getId());

    QString temp = "";
    identifier = new QLabel(t->getId(),this);
    title = new QLabel(t->getTitle(),this);
    duration = new QLabel(QString::number(t->getDuration().getHours())+"H"+QString::number(t->getDuration().getMinutes()),this);
    disponibility = new QLabel(t->getDisponibility().toString(),this);
    deadline = new QLabel(t->getDeadline().toString(),this);

    for (TasksIterator it = t->getIterator(); !(it.isDone()); it.next())
        temp += " "+it.current().getId();

    tasks = new QLabel(temp,this);

    formLayout = new QFormLayout(this);

    formLayout->addRow("id : ",identifier);
    formLayout->addRow("title : ",title);
    formLayout->addRow("duration",duration);
    formLayout->addRow("disponibility",disponibility);
    formLayout->addRow("deadline",deadline);
    formLayout->addRow("tasks : ",tasks);

    setLayout(formLayout);
}
