#include "Calendar.h"
#include <QDebug>

int main() {
    QTextStream cout(stdout, QIODevice::WriteOnly);
    try{
        Duration d1(23);
        cout<<d1<<"\n";
    }
    catch
    (CalendarException error) {cout<<error.getInfo();}

    return 0;
}
