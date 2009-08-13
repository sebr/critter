#include "AddReviewersAction.h"
#include "../Review.h"
#include "../RestCommunicator.h"
#include "../../Debug.h"

#include <QNetworkReply>

void AddReviewersAction::run() {
    m_communicator->postTextData(m_review->id() + "/reviewers", m_review->reviewers().join(","));
}

void AddReviewersAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not add reviewers to" << m_review->id() << ":" << reply->errorString();
}

void AddReviewersAction::callSuccessful(QNetworkReply *) {
    qDebug() << "Review Added";
    emit reviewersAdded();
}
