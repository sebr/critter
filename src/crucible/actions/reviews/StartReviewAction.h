#ifndef STARTREVIEWACTION_H
#define STARTREVIEWACTION_H

#include "AbstractReviewAction.h"

class QNetworkReply;

class StartReviewAction : public AbstractReviewAction
{
    Q_OBJECT

    public:
        StartReviewAction(Review *review, RestCommunicator *communicator, QObject *parent)
        : AbstractReviewAction(review, communicator, parent) {}
        virtual void run();

    signals:
        void reviewStarted();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // STARTREVIEWACTION_H
