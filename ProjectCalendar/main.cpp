#include "Calendar.h"
#include "Task.h"
#include "TaskManager.h"
#include "Association.h"
#include "Project.h"
#include "Event.h"
#include "Programmation.h"
#include "GUI-Architecture.h"
#include <QDebug>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

int main(int argc, char *argv[]) {
    QTextStream cout(stdout, QIODevice::WriteOnly);
//try{
        Duration d1(34);
        cout<<d1<<"\n";
        CompositeFactory* cf = &(CompositeFactory::getInstance());
        NonPreemptiveFactory* cnp = &(NonPreemptiveFactory::getInstance());
        PreemptiveFactory* cp = &(PreemptiveFactory::getInstance());
        CompositeTask& compo = cf->addTask("LO21","Programmation Objet",d1,QDate(2011,03,15),QDate(2050,02,13));
        PreemptiveTask& prem=cp->addTask("SI28","Ecriture multimedia",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        NonPreemptiveTask& prem2=cnp->addTask("TEST","Ecriture TEST",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        NonPreemptiveTask& prem3=cnp->addTask("TesTYY","TESTERRDZDZD",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        cf->addTask("RO03","Recherche Operationnelle",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        PreemptiveTask& ct9 = cp->addTask("BADEU","Trop Gros chiffre",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        cf->addTask("NF17","Conception base de donnee",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        cnp->addTask("LG62","Chinois niveau 2",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        CompositeTask& ct1 = cf->getTypedTask("RO03");
        ct1.addSubTask(ct9);
        ct1.addSubTask(prem2);
        cf = &(CompositeFactory::getInstance());
        qDebug()<<"PREMIERE ENUMERATION";
        CompositeFactory::DispoTasksIterationStrategy<2013,01,11> Strat1;
        PreemptiveFactory::PreemptiveTasksIterationStrategy Strat2;
        //Iterator<CompositeTask>::DispoTasksIterationStrategy<2014,01,11> Strat2;
        for (TasksIterator it = ct1.getIterator(&Strat1); !(it.isDone()); it.next())
            qDebug()<<it.current().getTitle();
        compo.addSubTask(prem);
        compo.addSubTask(prem3);
        compo.addSubTask(cf->getTask("LG62"));
        //compo.addSubTask(ct1);
        AssociationManager* am = &(AssociationManager::getInstance());
        //am->addAssociation(&ct1,&compo);
        am->addAssociation(&prem2,&prem3);
        //am->addAssociation(&compo,&ct1);
        //cf->removeTask(&ct1);
        //f->removeTask(&(cnp->getSubTypedTask("LG62")));
        qDebug()<<"DEUXIEME ENUMERATION";
        for (Iterator<PreemptiveTask> it = cp->getIterator<PreemptiveTask>(); !(it.isDone()); it.next()) { //we can improve the selection of task's subtype to enumerate
            qDebug()<<it.current().getId();
        }
        //compo.addSubTask(ct1);
        ProjectFactory* pf = &(ProjectFactory::getInstance());
        Project& pro1 = pf->addProject("Calendar","Project Agenda Calendar",Duration(1,30),QDate(1900,02,12),QDate(2500,05,06));
        qDebug()<<"premier project : "<<pro1.getTitle();
        CompositeFactory::ProjectValidTasksIterationStrategy Strat3;
        qDebug()<<"Les Valides : ";
        for (TasksIterator it = cf->getIterator(&Strat3); !(it.isDone()); it.next()) {
            qDebug()<<it.current().getId();
        }
        //pro1.addTask(compo);
        pro1.addTask(cp->getTask("NF17"));
        //pro1.addTask(ct1);
        //pf->removeProject(&pro1);
        //cf->freeInstance();
        // cp->freeInstance();
        //cnp->freeInstance();
        //pf->addProject("edfrev","zefdzed",Duration(0),QDate(1900,1,1),QDate(3000,1,1));
        CompositeTask& tempop = cf->addTask("zedzed","dzed",Duration(0),QDate(1940,1,1),QDate(2200,2,2));
        //tempop.addSubTask(compo);
        tempop.addSubTask(ct1);
        pro1.addTask(tempop);
        ProgrammationFactory* progF = &(ProgrammationFactory::getInstance());
        progF->scheduleTask(&prem2,"initialisation de la tache",QDate(2019,12,2),QTime(12,00),Duration(2,30),"Compy City");
        progF->scheduleTask(&prem3,"terminaison de la tache",QDate(2023,12,2),QTime(12,00),Duration(2,30),"Compy City");
        qDebug()<<progF->getSpecificEventByDateAndTime(QDate(2023,12,2),QTime(12,00))->getTask()->getId();
        progF->achieveEvent("initialisation de la tache");

/*    }
catch (CalendarException e) {
        qDebug()<<e.getInfo();
    }*/
    QApplication app(argc, argv);
    MainWindow wid;
    wid.show();

    return app.exec();
    //   return 0;
}
