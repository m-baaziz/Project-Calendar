#include "Calendar.h"
#include "Task.h"
#include <QDebug>

int main() {
    QTextStream cout(stdout, QIODevice::WriteOnly);
    try{
        Duration d1(34);
        cout<<d1<<"\n";
        CompositeFactory* cf = &(CompositeFactory::getInstance());
        CompositeTask& compo = cf->addTask("LO21","Programmation Objet",d1,QDate(2015,03,15),QDate(2017,02,13));
        qDebug()<<compo.getTitle();
        qDebug()<<cf->getTask("LO21").getTitle();
        cf->addTask("RO03","Recherche Operationnelle",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        cf->addTask("NF17","Conception base de donnee",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        CompositeTask& ct1 = cf->getTypedTask("RO03");
        //compo.addSubTask(cf->getTask("RO03"));
        qDebug()<<"enumeration :";
        cf = &(CompositeFactory::getInstance());
        for (CompositeFactory::TypedTasksIterator it = cf->getTypedTasksIterator(&ct1); !(it.isDone()); it.next())
            qDebug()<<it.current().getTitle();
        qDebug()<<"après for";
        PreemptiveFactory* cp = &(PreemptiveFactory::getInstance());
        PreemptiveTask& prem=cp->addTask("SI28","Ecriture multimedia",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        PreemptiveTask& prem2=cp->addTask("TEST","Ecriture TEST",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        compo.addSubTask(prem);
        compo.addSubTask(prem2);
        //ct1.addSubTask(cf->getTask("LO21"));
        NonPreemptiveFactory* cnp = &(NonPreemptiveFactory::getInstance());
        cnp->addTask("LG62","Chinois niveau 2",Duration(1,30),QDate(2013,02,12),QDate(2045,05,06));
        compo.addSubTask(cf->getTask("LG62"));
        compo.addSubTask(ct1);
        qDebug()<<"DEUXIEME ENUMERATION";
        for (PreemptiveFactory::SubTypedTasksIterator it = cp->getSubTypedTasksIterator(&compo); !(it.isDone()); it.next()) {
            qDebug()<<"debut du for du subtype";
            PreemptiveTask& toPrint = it.current();
            qDebug()<<"apres current du subtype";
            qDebug()<<toPrint.getId();
        }
    }
    catch
    (CalendarException error) {cout<<error.getInfo();}

    return 0;
}
