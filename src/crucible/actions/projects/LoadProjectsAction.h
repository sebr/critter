#ifndef LOADPROJECTSACTION_H
#define LOADPROJECTSACTION_H

#include "../AbstractAction.h"

class Project;
class QNetworkReply;

class LoadProjectsAction : public AbstractAction
{
    Q_OBJECT

    public:
        LoadProjectsAction(RestCommunicator *communicator, QObject *parent)
            : AbstractAction(communicator, parent) {}
        virtual void run();

    signals:
        void projectsReceived(QList<Project*> projects);

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // LOADPROJECTSACTION_H
