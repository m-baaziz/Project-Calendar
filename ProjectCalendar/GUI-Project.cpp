#include "GUI-Architecture.h"
#include "GUI-Project.h"

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

void NewProjectB::popProjectForm(){
    NewProjectForm* form = new NewProjectForm(this->parentWidget());
    form->show();
}

ProjectInfo::ProjectInfo(Project *t, QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Project "+t->getId());

    QString temp = "";
    identifier = new QLabel(t->getId(),this);
    title = new QLabel(t->getTitle(),this);
    unsigned int H = t->getDuration().getHours();
    unsigned int M = t->getDuration().getMinutes();
    QString h = (H<10)?"0"+QString::number(H):""+QString::number(H);
    QString m = (M<10)?"0"+QString::number(M):""+QString::number(M);
    duration = new QLabel(h+" H "+m,this);
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
