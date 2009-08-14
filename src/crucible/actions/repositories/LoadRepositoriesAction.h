#ifndef LOADREPOSITORIESACTION_H
#define LOADREPOSITORIESACTION_H

#include "../AbstractAction.h"

class Repository;
class QNetworkReply;

class LoadRepositoriesAction : public AbstractAction
{
    Q_OBJECT

    public:
        LoadRepositoriesAction(RestCommunicator *communicator, QObject *parent)
            : AbstractAction(communicator, parent) {}
        virtual void run();

    signals:
        void repositoriesReceived(QList<Repository*> projects);

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // LOADREPOSITORIESACTION_H
