#ifndef GUIASSOCIATION_H
#define GUIASSOCIATION_H
#include "GUI-Architecture.h"

class EditAssociationConstraint : public QDialog {
    Q_OBJECT

    QListView* predecessors;
    QListView* successors;
    Task* task;

    QPushButton* addB;
    QPushButton* removeB;
    QFormLayout* formLayout;

public :
    EditAssociationConstraint(Task* t, QWidget* parent);
public slots:
    void addAssociation();
    void removeAssociation();
};


#endif // GUIASSOCIATION_H
