#ifndef ADDREVIEWERSACTION_H
#define ADDREVIEWERSACTION_H

#include "AbstractAction.h"

class QNetworkReply;

class AddReviewersAction : public AbstractAction
{
    Q_OBJECT

    public:
        AddReviewersAction(const QUrl &server, Review *review,
                        RestCommunicator *communicator, QObject *parent)
            : AbstractAction(server, review, communicator, parent) {}
        virtual void run();

    signals:
        void reviewersAdded();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // ADDREVIEWERSACTION_H
