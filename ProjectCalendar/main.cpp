#include "Calendar.h"
#include "Task.h"
#include "Association.h"
#include <QDebug>

int main() {
    QTextStream cout(stdout, QIODevice::WriteOnly);
    try{
        Duration d1(34);
        cout<<d1<<"\n";
        CompositeFactory* cf = &(CompositeFactory::getInstance());
        NonPreemptiveFactory* cnp = &(NonPreemptiveFactory::getInstance());
        PreemptiveFactory* cp = &(PreemptiveFactory::getInstance());
        CompositeTask& compo = cf->addTask("LO21","Programmation Objet",d1,QDate(2015,03,15),QDate(2017,02,13));
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
        am->addAssociation(&ct1,&compo);
        //am->addAssociation(&compo,&ct1);
        cf->removeTask(&ct1);
        //f->removeTask(&(cnp->getSubTypedTask("LG62")));
        qDebug()<<"DEUXIEME ENUMERATION";
        for (Iterator<UnitaryTask> it = cp->getIterator<UnitaryTask>(&Strat2); !(it.isDone()); it.next()) { //we can improve the selection of task's subtype to enumerate
            qDebug()<<it.current().getId();
        }
        cf->freeInstance();
        cp->freeInstance();
        cnp->freeInstance();
    }
    catch
    (CalendarException error) {cout<<error.getInfo();}

    return 0;
}
