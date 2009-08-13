#ifndef CRUCIBLECONNECTOR_H
#define CRUCIBLECONNECTOR_H

#include <QObject>
#include <QNetworkReply>

class Review;
class RestCommunicator;

class CrucibleConnector : public QObject
{
    Q_OBJECT

    public:
        CrucibleConnector(QObject *parent);

        bool testConnection() const;

        void createReview(const Review *review);
        void updateReview(const Review *review);

    private slots:
        void createFailed(QNetworkReply *reply);
        void createSuccessful(QNetworkReply *reply);

    private:
        RestCommunicator *createCommunicator();

        QString m_server;
        QString m_user;
        QString m_password;
};

#endif // CRUCIBLECONNECTOR_H
