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

        void setReview(Review *review) { m_review = review; }

        void addReviewers();
        void createReview();
        void startReview();
        void updateReview();

    private slots:
        void createFailed(QNetworkReply *reply);
        void createSuccessful(QNetworkReply *reply);

        void reviewersFailed(QNetworkReply *reply);
        void reviewersSuccessful(QNetworkReply *reply);

        void startFailed(QNetworkReply *reply);
        void startSuccessful(QNetworkReply *reply);

    private:
        RestCommunicator *createCommunicator();

        Review *m_review;

        QString m_server;
        QString m_user;
        QString m_password;
};

#endif // CRUCIBLECONNECTOR_H
