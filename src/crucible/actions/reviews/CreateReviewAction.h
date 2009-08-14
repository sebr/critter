#ifndef CREATEREVIEWACTION_H
#define CREATEREVIEWACTION_H

#include "AbstractReviewAction.h"

class QNetworkReply;

class CreateReviewAction : public AbstractReviewAction
{
    Q_OBJECT

    public:
        CreateReviewAction(const QUrl &server, Review *review,
                    RestCommunicator *communicator, QObject *parent)
        : AbstractReviewAction(server, review, communicator, parent) {}
        virtual void run();

    signals:
        void reviewCreated();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // CREATEREVIEWACTION_H
