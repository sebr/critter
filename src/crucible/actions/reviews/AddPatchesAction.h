#ifndef ADDPATCHESACTION_H
#define ADDPATCHESACTION_H

#include "AbstractReviewAction.h"
#include <QStack>

class QNetworkReply;

class AddPatchesAction : public AbstractReviewAction
{
    Q_OBJECT

    public:
        AddPatchesAction(Review *review, RestCommunicator *communicator, QObject *parent)
            : AbstractReviewAction(review, communicator, parent) {}
        virtual void run();

    signals:
        void patchesAdded();

    protected:
        virtual void callFailed(QNetworkReply *reply);
        virtual void callSuccessful(QNetworkReply *reply);

    private:
        void doPatchQueue();
        QStack<QByteArray> m_patches;
};

#endif // ADDPATCHESACTION_H
