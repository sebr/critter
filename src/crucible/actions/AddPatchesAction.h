#ifndef ADDPATCHESACTION_H
#define ADDPATCHESACTION_H

#include "AbstractAction.h"
#include <QStack>

class QNetworkReply;

class AddPatchesAction : public AbstractAction
{
    Q_OBJECT

    public:
        AddPatchesAction(const QUrl &server, Review *review,
                        RestCommunicator *communicator, QObject *parent)
            : AbstractAction(server, review, communicator, parent) {}
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
