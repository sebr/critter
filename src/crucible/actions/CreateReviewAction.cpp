#include "CreateReviewAction.h"
#include "../Review.h"
#include "../RestCommunicator.h"
#include "../../Debug.h"

#include <QNetworkReply>

void CreateReviewAction::run() {
    DEBUG_BLOCK
    m_communicator->postData(QString(), m_review->createData());
}

void CreateReviewAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not create review at" << m_server << ":" << reply->errorString();
}

void CreateReviewAction::callSuccessful(QNetworkReply *reply) {
    QString location = reply->header(QNetworkRequest::LocationHeader).toUrl().toString();
    QString url = reply->url().toString();

    QString id = location.remove(url).mid(1);
    m_review->setId(id);

    debug() << "id:" << id;
    QString reviewUrl = m_server.toString(QUrl::StripTrailingSlash) + "/cru/" + id;

    qDebug() << "Created review:" << reviewUrl;

    emit reviewCreated();
}
