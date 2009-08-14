#include "StartReviewAction.h"
#include "../../Review.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>

void StartReviewAction::run() {
    m_communicator->post(m_review->id() + "/transition?action=action:approveReview");
}

void StartReviewAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not start review" << m_review->id() << ":" << reply->errorString();
}

void StartReviewAction::callSuccessful(QNetworkReply *) {
    qDebug() << "Review started";
    emit reviewStarted();
}
