#ifndef LOADUSERSACTION_H
#define LOADUSERSACTION_H

#include "../AbstractAction.h"

class User;
class QNetworkReply;

class LoadUsersAction : public AbstractAction
{
    Q_OBJECT

    public:
        LoadUsersAction(RestCommunicator *communicator, QObject *parent)
            : AbstractAction(communicator, parent) {}
        virtual void run();

    signals:
        void usersReceived(QList<User*> users);

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};


#endif // LOADUSERSACTION_H
