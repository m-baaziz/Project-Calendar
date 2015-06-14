#include "GUI-Architecture.h"

QStandardItemModel* MainWindow::tasksModel = new QStandardItemModel();
QStandardItemModel* MainWindow::projectsModel = new QStandardItemModel();
QStandardItemModel* MainWindow::eventsModel = new QStandardItemModel();
QStandardItemModel* MainWindow::independentTasksModel = new QStandardItemModel();
QStandardItemModel* MainWindow::projectsTreeModel = new QStandardItemModel();

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    this->resize(1400,950);


    mainLayer = new QVBoxLayout(this);
    topLayer = new QHBoxLayout(this);
    workSpaceLayer = new QHBoxLayout(this);
    itemsMenuLayer = new QVBoxLayout(this);
    displayLayer = new QVBoxLayout(this);

    // in topLayer

    newProjectB = new NewProjectB("New Project",this);
    newTaskB = new NewTaskB("New Task",this);
    calendarB = new QPushButton("Calendar",this);

    calendarB->connect(calendarB,SIGNAL(clicked()),this,SLOT(showCalendar()));

    topLayer->addWidget(newProjectB);
    topLayer->addWidget(newTaskB);
    topLayer->addWidget(calendarB);

    // in itemsMenuLayer

    itemTypeSelector = new MyComboBox(this);
    projectsTree = new QTreeView(this);
    projectsTreeView = new QTreeView(this);
    independentTasksTree = new QTreeView(this);
    projectsTree->setModel(projectsModel);
    projectsTreeView->setModel(projectsTreeModel);
    independentTasksTree->setModel(independentTasksModel);
    independentTasksTree->hide();
    projectsTree->hide();

    projectsTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(projectsTree, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showProjectContextMenu(const QPoint&)));

    independentTasksTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(independentTasksTree, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showTaskContextMenu(const QPoint&)));

    projectsTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(projectsTreeView,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(showProjectContextMenu(QPoint)));

    itemTypeSelector->addItem("Projects");
    itemTypeSelector->addItem("Independent Tasks");
    itemTypeSelector->addItem("Projects Trees");

    itemsMenuLayer->addWidget(itemTypeSelector);
    itemsMenuLayer->addWidget(projectsTree);
    itemsMenuLayer->addWidget(projectsTreeView);
    itemsMenuLayer->addWidget(independentTasksTree);

    //setProjectsInMenu(); // no need to call it, already done by the first "indexChanged" event on MyComboBox
    //setEventsInMenu();
    setIndependentTasksInMenu();
    setTasksInModel();
    setProjectsTreeModel();

    // in displayLayer
    calendarTable = new Week(this);
    treeScene = new QGraphicsScene;
    treeView = new QGraphicsView(treeScene);

    treeScene->setSceneRect(300,50,500,500);
    treeView->setScene(treeScene);
    treeView->hide();

    displayLayer->addWidget(calendarTable);
    displayLayer->addWidget(treeView);


    // bottom Event Layer

    eventForm = new EventForm(this);
    eventLayer = new QHBoxLayout(this);
    eventLayer->addWidget(eventForm);
    //////////////////////////////////////



    mainLayer->addLayout(topLayer);
    workSpaceLayer->addLayout(itemsMenuLayer,1);
    workSpaceLayer->addLayout(displayLayer,4);
    mainLayer->addLayout(workSpaceLayer);
    mainLayer->addLayout(eventLayer);


    setLayout(mainLayer);
}

void MainWindow::showCalendar() {
    treeView->hide();
    calendarTable->show();
    refreshCalendar();
}

void MainWindow::refreshCalendar() {
    calendarTable->updateWeek();
}

void MainWindow::treeDepth(QModelIndex currentIndex,unsigned int* depth,unsigned int tempDepth) {
    tempDepth++;
    int count = 0;
    for (unsigned int i = 0; i < projectsTreeModel->rowCount(currentIndex); i++) {
        count ++;
        treeDepth(currentIndex.child(i,0),depth,tempDepth);
    }
    if (count==0 && tempDepth>*depth) *depth=tempDepth;

}

void MainWindow::drawTreeHelper(const unsigned int Y,const unsigned int X, std::vector<ProjectTreeNode>& V, QModelIndex father,unsigned int space) {
    NonPreemptiveFactory* npf = &(NonPreemptiveFactory::getInstance());
    int y = Y+100;
    int diametre = 40;
    int nodeStartOffset=0;
    unsigned int sonNB = projectsTreeModel->rowCount(father);
    if (sonNB>0){
        space=space/2;
        if (space<diametre && sonNB>1) diametre = space;
        nodeStartOffset = (sonNB/2)*space;
    }
    int FX=X;
    int FY=Y;
    for (std::vector<ProjectTreeNode>::iterator it=V.begin(); it!=V.end(); ++it){
        if ((*it).id.data().toString()==father.data().toString()) {
            FX = (*it).x;      // we save father's coordinates in order to make connection edges with its sons.
            FY = (*it).y;
        }
    }
    int posInc = 0;
    int negInc = 0;
    int x;
    for (unsigned int i = 0; i<sonNB; i++) {
        if (i%2==0) {
            x = X-nodeStartOffset+posInc*space;
            posInc++;
        }
        else {
            x = X-nodeStartOffset+(sonNB*space)-negInc*space;
            negInc++;
        }
        QString id = father.child(i,0).data().toString();
        bool present = false;
        for (std::vector<ProjectTreeNode>::iterator it=V.begin(); it!=V.end(); ++it){
            if ((*it).id.data().toString()==id) {
                present = true;
                treeScene->addLine(FX+20,FY+20,(*it).x+20,(*it).y+20,QPen(QColor("black"),2));
                treeScene->addPolygon(ArrowHead((*it).x,(*it).y,FX,FY),QPen(QColor("black")),QBrush(Qt::GlobalColor::black));
            }
        }
        if (present) {   // we don't draw the node if it has already been drawn
            continue;
        }
        treeScene->addPolygon(ArrowHead(x,y,FX,FY),QPen(QColor("black")),QBrush(Qt::GlobalColor::black));
        treeScene->addLine(FX+20,FY+20,x+20,y+20,QPen(QColor("black"),2));
        if (npf->getTask(id).isTaskCompleted())
            treeScene->addEllipse(x,y,diametre,diametre,QPen(QBrush(QColor("black")),3),QBrush(QColor(0,255,103)));
        else
            treeScene->addEllipse(x,y,diametre,diametre,QPen(QBrush(QColor("black")),3));
        treeScene->addSimpleText(id)->setPos(x-20,y-15);
        V.push_back(ProjectTreeNode(father.child(i,0),x,y)); // 10 : temporary value
    }
    for (unsigned int i = 0; i<sonNB; i++) {
        int x = X-space+i*space;
        drawTreeHelper(y,x,V,father.child(i,0),space);
    }

}

void MainWindow::drawProjectTree(QModelIndex projectIndex) {
    std::vector<ProjectTreeNode> V;
    treeScene->addSimpleText(projectIndex.data().toString())->setPos(500,40);
    if (projectsTreeModel->rowCount(projectIndex) != 0) {
        drawTreeHelper(40,500,V,projectIndex,1000/projectsTreeModel->rowCount(projectIndex));
        unsigned int maxY = 0;  // the maximum y coordinate, helps us to place the last "end" node.
        for (std::vector<ProjectTreeNode>::iterator it = V.begin(); it!=V.end(); ++it) if ((*it).y>maxY) maxY=(*it).y;
        treeScene->addSimpleText("END")->setPos(500,maxY+100);
        for (std::vector<ProjectTreeNode>::iterator it = V.begin(); it!=V.end(); ++it) {
            if (projectsTreeModel->rowCount((*it).id)==0) {
                treeScene->addLine((*it).x+20,(*it).y+20,500+20,maxY+100,QPen(QColor("purple"),2));
                treeScene->addPolygon(ArrowHead(500,maxY+80,(*it).x,(*it).y),QPen(QColor("black")),QBrush(Qt::GlobalColor::black));
            }
        }
    }
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

void MainWindow::setProjectsTreeModel() {
    QStandardItem* parent = projectsTreeModel->invisibleRootItem();
    for (Iterator<Project> itp = ProjectFactory::getInstance().getIterator(); !(itp.isDone()); itp.next()) {
        QStandardItem* tempP = new QStandardItem(itp.current().getId());  // gonna need to manage those items, and delete them at the end of the process
        tempP->setFlags(tempP->flags() & ~Qt::ItemIsEditable);
        parent->appendRow(tempP);
        TasksContainer rootTasks = itp.current().getRootTasks();
        for (TasksContainer::iterator it = rootTasks.begin(); it!=rootTasks.end() ; ++it){
            QStandardItem* temp = new QStandardItem((*it)->getId());
            temp->setFlags(temp->flags() & ~Qt::ItemIsEditable);
            tempP->appendRow(temp);
            TasksContainer successors = AssociationManager::getInstance().getTaskSuccessors(*it);
            for (TasksContainer::iterator it2 = successors.begin(); it2!=successors.end(); ++it2) {
                injectSuccessorInModel(temp,*(*it2), itp.current());
            }
        }
    }
}


void MainWindow::injectSuccessorInModel(QStandardItem* parent, Task& son, Project& proj) {
    QStandardItem* temp = new QStandardItem(son.getId());
    temp->setFlags(temp->flags() & ~Qt::ItemIsEditable);
    parent->appendRow(temp);
    TasksContainer successors = AssociationManager::getInstance().getTaskSuccessors(&son);
    for (TasksContainer::iterator it = successors.begin(); it!=successors.end(); ++it) {
        injectSuccessorInModel(temp,*(*it),proj);
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
    projectsTreeView->hide();
    independentTasksTree->hide();
    projectsTree->show();
}

void MainWindow::showProjectsTreeInMenu() {
    refreshProjectsTreeModel();
    projectsTree->hide();
    independentTasksTree->hide();
    projectsTreeView->show();
}

void MainWindow::showIndependentTasksInMenu() {
    refreshIndependentTasksModel();
    projectsTree->hide();
    independentTasksTree->show();
    projectsTreeView->hide();
}

void MainWindow::showProjectContextMenu(const QPoint &pos) {
    QPoint globalPos = projectsTree->mapToGlobal(pos);
    QMenu* menu = new QMenu(this);
    Project* proj;
    Task* t;
    QString selectedProject = projectsTree->indexAt(pos).data(Qt::DisplayRole).toString();
    if (!(projectsTreeView->isHidden()))
        selectedProject = projectsTreeView->indexAt(pos).data(Qt::DisplayRole).toString();
    try {
        proj = &(ProjectFactory::getInstance().getProject(selectedProject));
        menu->addAction("add tasks");
        menu->addAction("infos");
        menu->addAction("show tree");
        menu->addAction("remove");

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
        if (selectedItem && selectedItem->text()=="show tree") {
            treeScene->clear();
            if (projectsTreeView->isHidden()) {
                itemTypeSelector->setCurrentIndex(2);
                drawProjectTree(projectsTreeView->indexAt(pos));  // called from the projectsTreeView
            }
            else {
                drawProjectTree(projectsTreeView->indexAt(pos));    // called from the projectsTree
            }
            calendarTable->hide();
            treeView->show();
        }
    }
    catch (CalendarException e) {


        QString selectedTask = projectsTree->indexAt(pos).data(Qt::DisplayRole).toString();
        if (!(projectsTreeView->isHidden()))
            selectedTask = projectsTreeView->indexAt(pos).data(Qt::DisplayRole).toString();
    try {
        t = &(NonPreemptiveFactory::getInstance().getTask(selectedTask));
        if (t->getTaskType()==COMPOSITE) menu->addAction("add subtasks");
        else {
            UnitaryTask* ut = &(NonPreemptiveFactory::getInstance().getTypedTask(selectedTask));
            menu->addAction("schedule programmation");
        }
        menu->addAction("edit constraints");
        menu->addAction("infos");
        menu->addAction("remove");

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
        if (selectedItem && selectedItem->text()=="edit constraints") {
            EditAssociationConstraint* editc = new EditAssociationConstraint(t,this);
            editc->show();
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
            menu->addAction("schedule programmation");
        }
        menu->addAction("edit constraints");
        menu->addAction("infos");
        menu->addAction("remove");
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
    if (selectedItem && selectedItem->text()=="edit constraints") {
        EditAssociationConstraint* editc = new EditAssociationConstraint(t,this);
        editc->show();
    }
}

void MyComboBox::handleSelectionChanged(int index){
    if (index==0) dynamic_cast<MainWindow*>(parent())->showProjectsInMenu();
    if (index==1) dynamic_cast<MainWindow*>(parent())->showIndependentTasksInMenu();
    if (index==2) dynamic_cast<MainWindow*>(parent())->showProjectsTreeInMenu();
}


void MainWindow::refreshProjectsModel() {
    MainWindow::projectsModel->clear();
    setProjectsInMenu();
    refreshTasksModel();
}

void MainWindow::refreshIndependentTasksModel() {
    independentTasksModel->clear();
    setIndependentTasksInMenu();
    refreshTasksModel();
}

void MainWindow::refreshTasksModel() {
    tasksModel->clear();
    setTasksInModel();
    refreshProjectsTreeModel();
}

void MainWindow::refreshProjectsTreeModel() {
    projectsTreeModel->clear();
    setProjectsTreeModel();
}



