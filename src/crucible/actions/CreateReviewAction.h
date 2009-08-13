#ifndef CREATEREVIEWACTION_H
#define CREATEREVIEWACTION_H

#include "AbstractAction.h"

class QNetworkReply;

class CreateReviewAction : public AbstractAction
{
    Q_OBJECT

    public:
        CreateReviewAction(const QUrl &server, Review *review,
                    RestCommunicator *communicator, QObject *parent)
        : AbstractAction(server, review, communicator, parent) {}
        virtual void run();

    signals:
        void reviewCreated();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);
};

#endif // CREATEREVIEWACTION_H
