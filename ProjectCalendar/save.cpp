#include "save.h"

void saveAll(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException("Error : Can't open the file "+fileName+" pleas make sure that this file is not open");
    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("ProjectCalendar");
    NonPreemptiveFactory::getInstance().save(stream);
    ProjectFactory::getInstance().save(stream);
    AssociationManager::getInstance().save(stream);
    ProgrammationFactory::getInstance().save(stream);
    stream.writeEndElement();
    stream.writeEndDocument();
    file.close();
}

void loadAll(const QString &fileName) {
    ProgrammationFactory::getInstance().freeInstance();
    ActivityFactory::getInstance().freeInstance();
    ActivityFactory::getInstance().freeInstance();
    ProjectFactory::getInstance().freeInstance();
    AssociationManager::getInstance().freeInstance();
    CompositeFactory::getInstance().freeInstance();
    PreemptiveFactory::getInstance().freeInstance();
    NonPreemptiveFactory::getInstance().freeInstance();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw CalendarException("Error : Can't open the file "+fileName);
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        if(xml.tokenType()==QXmlStreamReader::StartDocument) {
            xml.readNext();
            continue;
        }
        if (xml.tokenType()==QXmlStreamReader::StartElement) {
            if (xml.name().toString()=="Tasks") loadTasks(xml);
            if (xml.name().toString()=="Projects") loadProjects(xml);
            if (xml.name().toString()=="Associations") loadAssociations(xml);
            if (xml.name().toString()=="Events") loadEvents(xml);
        }
        xml.readNext();
    }
    if (xml.hasError())
        throw CalendarException("Error : xml parser error");
    xml.clear();
}

void loadTasks(QXmlStreamReader& xml) {
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    bool completed;
    bool preemptive;
    std::map<QString,QStringList> subtasks;  // QString -> composite Task id, QStringList -> its subtasks

    CompositeTask* tempCompo;
    CompositeFactory* cf = &(CompositeFactory::getInstance());
    NonPreemptiveFactory* cnp = &(NonPreemptiveFactory::getInstance());
    PreemptiveFactory* cp = &(PreemptiveFactory::getInstance());

    xml.readNext();
    while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Tasks")) {
        if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Unitary") {
                xml.readNext();
                while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Unitary")) {
                    if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Task") {
                            xml.readNext();
                            while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Task")) {
                                if (xml.tokenType()==QXmlStreamReader::StartElement) {
                                    if (xml.name()=="identifier") {
                                        xml.readNext();
                                        identifier=xml.text().toString();
                                    }
                                    if (xml.name()=="title") {
                                        xml.readNext();
                                        title=xml.text().toString();
                                    }
                                    if (xml.name()=="duration") {
                                        xml.readNext();
                                        duration=Duration().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="disponibility") {
                                        xml.readNext();
                                        disponibility=QDate().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="deadline") {
                                        xml.readNext();
                                        deadline=QDate().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="isCompleted") {
                                        xml.readNext();
                                        completed = (xml.text().toString()=="true")?true:false;
                                    }
                                    if (xml.name()=="preemptive") {
                                        xml.readNext();
                                        preemptive = (xml.text().toString()=="true")?true:false;
                                    }
                                }
                                xml.readNext();
                            }
                            try {
                                if (preemptive) cp->addTask(identifier,title,duration,disponibility,deadline);
                                else cnp->addTask(identifier,title,duration,disponibility,deadline);
                            }
                            catch (CalendarException e) {
                                QMessageBox* error = new QMessageBox();
                                error->setText(e.getInfo());
                                error->show();
                            }
                       }
                       xml.readNext();
                }
            }
            if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Composite") {
                xml.readNext();
                while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Composite")) {
                    if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Task") {
                            xml.readNext();
                            while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Task")) {
                                if (xml.tokenType()==QXmlStreamReader::StartElement) {
                                    if (xml.name()=="identifier") {
                                        xml.readNext();
                                        identifier=xml.text().toString();
                                    }
                                    if (xml.name()=="title") {
                                        xml.readNext();
                                        title=xml.text().toString();
                                    }
                                    if (xml.name()=="duration") {
                                        xml.readNext();
                                        duration=Duration().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="disponibility") {
                                        xml.readNext();
                                        disponibility=QDate().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="deadline") {
                                        xml.readNext();
                                        deadline=QDate().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="isCompleted") {
                                        xml.readNext();
                                        completed = (xml.text().toString()=="true")?true:false;
                                    }
                                    if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="subtasks") {
                                        xml.readNext();
                                        QStringList buffer;
                                        while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="subtasks")) {
                                            if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="identifier") {
                                                xml.readNext();
                                                buffer.push_back(xml.text().toString());
                                            }
                                            xml.readNext();
                                        }
                                        subtasks[identifier]=buffer;
                                    }
                                }
                                xml.readNext();
                            }
                            try {
                                tempCompo = &(cf->addTask(identifier,title,duration,disponibility,deadline));
                            }
                            catch (CalendarException e) {
                                QMessageBox* error = new QMessageBox();
                                error->setText(e.getInfo());
                                error->show();
                            }
                       }
                       else xml.readNext();
                }
            }
            xml.readNext();
        }
    for (std::map<QString,QStringList>::iterator it=subtasks.begin(); it!=subtasks.end(); ++it) {
        for (QStringList::iterator itT = it->second.begin(); itT!=it->second.end(); ++itT)
            cf->getTypedTask(it->first).addSubTask(cf->getTask(*itT));
    }
    if (xml.hasError())
        throw CalendarException("Error : xml parser error");
}

void loadProjects(QXmlStreamReader& xml) {
    QString identifier;
    QString title;
    Duration duration;
    QDate disponibility;
    QDate deadline;
    bool completed;
    QStringList tasks;  // QString -> composite Task id, QStringList -> its subtasks

    Project* tempProj;
    ProjectFactory* pf = &(ProjectFactory::getInstance());
    NonPreemptiveFactory* npf = &(NonPreemptiveFactory::getInstance());

    xml.readNext();
    while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Projects")) {
        if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Project") {
            xml.readNext();
            while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Project")) {
                if (xml.tokenType()==QXmlStreamReader::StartElement) {
                    if (xml.name()=="identifier") {
                        xml.readNext();
                        identifier=xml.text().toString();
                    }
                    if (xml.name()=="title") {
                        xml.readNext();
                        title=xml.text().toString();
                    }
                    if (xml.name()=="duration") {
                        xml.readNext();
                        duration=Duration().fromString(xml.text().toString());
                    }
                    if (xml.name()=="disponibility") {
                        xml.readNext();
                        disponibility=QDate().fromString(xml.text().toString());
                    }
                    if (xml.name()=="deadline") {
                        xml.readNext();
                        deadline=QDate().fromString(xml.text().toString());
                    }
                    if (xml.name()=="isCompleted") {
                        xml.readNext();
                        completed = (xml.text().toString()=="true")?true:false;
                    }
                    if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Tasks") {
                        xml.readNext();
                        tasks.clear();
                        while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Tasks")) {
                            if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="identifier") {
                                xml.readNext();
                                tasks.push_back(xml.text().toString());
                            }
                            xml.readNext();
                        }
                    }
                }
                xml.readNext();
            }
            try {
                tempProj = &(pf->addProject(identifier,title,duration,disponibility,deadline));
                for (QStringList::iterator it=tasks.begin(); it!=tasks.end(); ++it)
                    tempProj->addTask(npf->getTask(*it));
            }
            catch (CalendarException e) {
                QMessageBox* error = new QMessageBox();
                error->setText(e.getInfo());
                error->show();
            }
        }
        xml.readNext();
    }
    if (xml.hasError())
        throw CalendarException("Error : xml parser error");
}

void loadAssociations(QXmlStreamReader& xml) {
    QString predecessor;
    QString successor;
    Task* taskP;
    Task* taskS;

    AssociationManager* am = &(AssociationManager::getInstance());
    NonPreemptiveFactory* npf = &(NonPreemptiveFactory::getInstance());

    xml.readNext();
    while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Associations")) {
        if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Association") {
            xml.readNext();
            while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Association")) {
                if (xml.tokenType()==QXmlStreamReader::StartElement) {
                    if (xml.name()=="predecessor") {
                        xml.readNext();
                        predecessor=xml.text().toString();
                    }
                    if (xml.name()=="successor") {
                        xml.readNext();
                        successor=xml.text().toString();
                    }
                }
                xml.readNext();
            }
            taskP = &(npf->getTask(predecessor));
            taskS = &(npf->getTask(successor));
            try {
                if (!(am->isTaskXFollowedByY(taskP,taskS))) am->addAssociation(taskP,taskS);
            }
            catch (CalendarException e) {
                QMessageBox* error = new QMessageBox();
                error->setText(e.getInfo());
                error->show();
            }
        }
        xml.readNext();
    }
    if (xml.hasError())
        throw CalendarException("Error : xml parser error");
}

void loadEvents(QXmlStreamReader& xml) {
    QString name;
    QDate date;
    QTime time;
    Duration duration;
    QString place;
    QStringList participants;
    QString type;
    QString task;
    bool achieved;
    std::map<QString,bool> isEventAchieved;    // QString -> event name, bool -> achieved or not

    ProgrammationFactory* pf = &(ProgrammationFactory::getInstance());
    ActivityFactory* af = &(ActivityFactory::getInstance());
    NonPreemptiveFactory* npf = &(NonPreemptiveFactory::getInstance());

    xml.readNext();
    while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Events")) {
        if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Activities") {
                xml.readNext();
                while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Activities")) {
                    if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Activity") {
                            xml.readNext();
                            while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Activity")) {
                                if (xml.tokenType()==QXmlStreamReader::StartElement) {
                                    if (xml.name()=="name") {
                                        xml.readNext();
                                        name=xml.text().toString();
                                    }
                                    if (xml.name()=="date") {
                                        xml.readNext();
                                        date=QDate().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="time") {
                                        xml.readNext();
                                        time=QTime().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="duration") {
                                        xml.readNext();
                                        duration=Duration().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="place") {
                                        xml.readNext();
                                        place=xml.text().toString();
                                    }
                                    if (xml.name()=="participants") {
                                        xml.readNext();
                                        participants=xml.text().toString().split(",");
                                    }
                                    if (xml.name()=="achieved") {
                                        xml.readNext();
                                        achieved = (xml.text().toString()=="true")?true:false;
                                    }
                                    if (xml.name()=="type") {
                                        xml.readNext();
                                        type=xml.text().toString();
                                    }
                                }
                                xml.readNext();
                            }
                            try {
                                af->addActivity(name,date,time,duration,place,getActivityType(type),participants);
                                isEventAchieved[name]=achieved;
                            }
                            catch (CalendarException e) {
                                QMessageBox* error = new QMessageBox();
                                error->setText(e.getInfo());
                                error->show();
                            }
                       }
                       xml.readNext();
                }
                for (std::map<QString,bool>::iterator it=isEventAchieved.begin(); it!=isEventAchieved.end(); ++it) {
                    if (it->second) pf->achieveEvent(it->first);
                }
            }
            if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Programmations") {
                xml.readNext();
                while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Programmations")) {
                    if (xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="Programmation") {
                            xml.readNext();
                            while (!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="Programmation")) {
                                if (xml.tokenType()==QXmlStreamReader::StartElement) {
                                    if (xml.name()=="name") {
                                        xml.readNext();
                                        name=xml.text().toString();
                                    }
                                    if (xml.name()=="date") {
                                        xml.readNext();
                                        date=QDate().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="time") {
                                        xml.readNext();
                                        time=QTime().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="duration") {
                                        xml.readNext();
                                        duration=Duration().fromString(xml.text().toString());
                                    }
                                    if (xml.name()=="place") {
                                        xml.readNext();
                                        place=xml.text().toString();
                                    }
                                    if (xml.name()=="participants") {
                                        xml.readNext();
                                        participants=xml.text().toString().split(",");
                                    }
                                    if (xml.name()=="achieved") {
                                        xml.readNext();
                                        achieved = (xml.text().toString()=="true")?true:false;
                                    }
                                    if (xml.name()=="task") {
                                        xml.readNext();
                                        task=xml.text().toString();
                                    }
                                }
                                xml.readNext();
                            }
                            try {
                                 pf->scheduleTask(&(npf->getTypedTask(task)),name,date,time,duration,place,participants);
                                 isEventAchieved[name]=achieved;
                            }
                            catch (CalendarException e) {
                                QMessageBox* error = new QMessageBox();
                                error->setText(e.getInfo());
                                error->show();
                            }
                       }
                       else xml.readNext();
                }
                for (std::map<QString,bool>::iterator it=isEventAchieved.begin(); it!=isEventAchieved.end(); ++it) {
                    if (it->second) pf->achieveEvent(it->first);
                }
            }
            xml.readNext();
        }
    if (xml.hasError())
        throw CalendarException("Error : xml parser error");
}
