#ifndef SAVE_H
#define SAVE_H
#include "Calendar.h"
#include "Task.h"
#include "TaskManager.h"
#include "Association.h"
#include "Project.h"
#include "Event.h"
#include "Programmation.h"

#include <QMessageBox>

void saveAll(const QString& fileName);
void loadTasks(QXmlStreamReader& xml);
void loadProjects(QXmlStreamReader& xml);
void loadAssociations(QXmlStreamReader& xml);
void loadEvents(QXmlStreamReader& xml);
void loadAll(const QString& fileName);

#endif // SAVE_H
