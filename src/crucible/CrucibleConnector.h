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
        void setServer(const QString &server);

        void createReview();
        void updateReview();

    private slots:
        void updateReviewContent();

    private:
        void addReviewers();
        void startReview();
        void addChangesets();
        void addPatches();

        RestCommunicator *createCommunicator();

        Review *m_review;

        QUrl m_server;
        QString m_user;
        QString m_password;
};

#endif // CRUCIBLECONNECTOR_H
