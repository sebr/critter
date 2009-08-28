#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QObject>

class RestCommunicator;
class QNetworkReply;

class AbstractAction : public QObject
{
    Q_OBJECT

    public:
        AbstractAction(RestCommunicator *communicator, QObject *parent);
        virtual ~AbstractAction() {}

        virtual void run() = 0;

    private slots:
        void callFailedSlot(QNetworkReply *reply);
        void callSuccessfulSlot(QNetworkReply *reply);

    protected:
        virtual void init();

        virtual void callFailed(QNetworkReply *reply) = 0;
        virtual void callSuccessful(QNetworkReply *reply) = 0;

        RestCommunicator *m_communicator;
};

#endif // ABSTRACTACTION_H
