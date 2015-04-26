#include "Calendar.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

void Duration::display(QTextStream &flow) const {
    flow.setPadChar('0');
    flow.setFieldWidth(2);
    flow<<getHours();
    flow.setFieldWidth(0);
    flow<<"H";
    flow.setFieldWidth(2);
    flow<<getMinutes();
    flow.setPadChar(' ');
    flow.setFieldWidth(0);
}

QTextStream& operator<<(QTextStream& flow, const Duration& d){
    d.display(flow);
    return flow;
}

QTextStream& operator>>(QTextStream& flow, Duration& d){
    unsigned int h,m;
    bool ok=true;
    flow>>h;
    if (flow.status()!=QTextStream::Ok) ok=false;

    if(flow.read(1)=="H") {
        flow>>m;
        if (flow.status()!=QTextStream::Ok) ok=false;
    }
    else {
        ok=false;
    }
    if (ok) d=Duration(h,m);
    return flow;
}




