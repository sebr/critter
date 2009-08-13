#ifndef ADDCHANGESETSACTION_H
#define ADDCHANGESETSACTION_H

#include "AbstractAction.h"

class QNetworkReply;

class AddChangesetsAction : public AbstractAction
{
    Q_OBJECT

    public:
        AddChangesetsAction(const QUrl &server, Review *review,
                        RestCommunicator *communicator, QObject *parent)
            : AbstractAction(server, review, communicator, parent) {}
        virtual void run();

    signals:
        void changesetsAdded();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // ADDCHANGESETSACTION_H
