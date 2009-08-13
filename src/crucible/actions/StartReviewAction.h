#ifndef STARTREVIEWACTION_H
#define STARTREVIEWACTION_H

#include "AbstractAction.h"

class QNetworkReply;

class StartReviewAction : public AbstractAction
{
    Q_OBJECT

    public:
        StartReviewAction(const QUrl &server, Review *review,
                    RestCommunicator *communicator, QObject *parent)
        : AbstractAction(server, review, communicator, parent) {}
        virtual void run();

    signals:
        void reviewStarted();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // STARTREVIEWACTION_H
