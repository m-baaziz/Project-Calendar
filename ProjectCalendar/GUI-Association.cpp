#include "GUI-Architecture.h"
#include "GUI-Association.h"

void EditAssociationConstraint::addAssociation() {
    AssociationManager* am = &(AssociationManager::getInstance());
    NonPreemptiveFactory* factory = &(NonPreemptiveFactory::getInstance());
    try {
        foreach (const QModelIndex &index,predecessors->selectionModel()->selectedIndexes())
                am->addAssociation(&(factory->getTask(MainWindow::tasksModel->itemFromIndex(index)->text())),task);
        foreach (const QModelIndex &index,successors->selectionModel()->selectedIndexes())
                am->addAssociation(task,&(factory->getTask(MainWindow::tasksModel->itemFromIndex(index)->text())));
        dynamic_cast<MainWindow*>(QWidget::window())->refreshProjectsTreeModel();
        this->destroy();
    }
    catch (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
    }
}

EditAssociationConstraint::EditAssociationConstraint(Task *t, QWidget *parent) : task(t), QDialog(parent) {
    predecessors = new QListView(this);
    successors = new QListView(this);
    predecessors->setSelectionMode(QAbstractItemView::MultiSelection);
    successors->setSelectionMode(QAbstractItemView::MultiSelection);
    predecessors->setModel(MainWindow::tasksModel);
    successors->setModel(MainWindow::tasksModel);

    addB = new QPushButton("Add",this);
    addB->connect(addB,SIGNAL(clicked()),this,SLOT(addAssociation()));
    removeB = new QPushButton("Remove",this);
    removeB->connect(removeB,SIGNAL(clicked()),this,SLOT(removeAssociation()));
    formLayout = new QFormLayout(this);
    formLayout->addRow("predecessors : ",predecessors);
    formLayout->addRow("successors : ",successors);
    formLayout->addRow(addB);
    formLayout->addRow(removeB);

    setLayout(formLayout);
}


void EditAssociationConstraint::removeAssociation() {
    AssociationManager* am = &(AssociationManager::getInstance());
    NonPreemptiveFactory* factory = &(NonPreemptiveFactory::getInstance());
    try {
        foreach (const QModelIndex &index,predecessors->selectionModel()->selectedIndexes())
                am->removeAssociation(&(factory->getTask(MainWindow::tasksModel->itemFromIndex(index)->text())),task);
        foreach (const QModelIndex &index,successors->selectionModel()->selectedIndexes())
                am->removeAssociation(task,&(factory->getTask(MainWindow::tasksModel->itemFromIndex(index)->text())));
        dynamic_cast<MainWindow*>(QWidget::window())->refreshProjectsTreeModel();
        this->destroy();
    }
    catch (CalendarException e) {
        QMessageBox* errMessage = new QMessageBox(this);
        errMessage->setText(e.getInfo());
        errMessage->show();
    }
}

