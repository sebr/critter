#ifndef CRUCIBLECONNECTOR_H
#define CRUCIBLECONNECTOR_H

#include "CrucibleConnectorBase.h"

#include <QObject>
#include <QNetworkReply>

class Review;
class RestCommunicator;

class CrucibleConnector : public CrucibleConnectorBase
{
    Q_OBJECT

    public:
        CrucibleConnector(QObject *parent);

        void setReview(Review *review) { m_review = review; }

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
};

#endif // CRUCIBLECONNECTOR_H
