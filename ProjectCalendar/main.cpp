#include "Calendar.h"
#include "Task.h"
#include <QDebug>

int main() {
    QTextStream cout(stdout, QIODevice::WriteOnly);
    try{
        Duration d1(32);
        cout<<d1<<"\n";
        CompositeFactory* cf = &(CompositeFactory::getInstance());
        CompositeTask& compo = cf->addTask("LO21","Programmation Objet",d1,QDate(2015,03,15),QDate(2017,02,13));
        qDebug()<<"Ici ? 4";
        qDebug()<<compo.getTitle();
        qDebug()<<cf->getTask("LO21").getTitle();
        cf->freeInstance();
    }
    catch
    (CalendarException error) {cout<<error.getInfo();}

    return 0;
}
