#include "AddReviewersAction.h"
#include "../../Review.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>

void AddReviewersAction::run() {
    m_communicator->postTextData(m_review->id() + "/reviewers", m_review->reviewers().join(","));
}

void AddReviewersAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not add reviewers to" << m_review->id() << ":" << reply->errorString();
}

void AddReviewersAction::callSuccessful(QNetworkReply *reply) {
    Q_UNUSED(reply)
    const int c = m_review->reviewers().size();
    qDebug() << "Added" << c << (c > 1 ? "reviewers" : "reviewer");
    emit reviewersAdded();
}
