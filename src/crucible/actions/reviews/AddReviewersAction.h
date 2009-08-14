#ifndef ADDREVIEWERSACTION_H
#define ADDREVIEWERSACTION_H

#include "AbstractReviewAction.h"

class QNetworkReply;

class AddReviewersAction : public AbstractReviewAction
{
    Q_OBJECT

    public:
        AddReviewersAction(const QUrl &server, Review *review,
                        RestCommunicator *communicator, QObject *parent)
            : AbstractReviewAction(server, review, communicator, parent) {}
        virtual void run();

    signals:
        void reviewersAdded();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // ADDREVIEWERSACTION_H
