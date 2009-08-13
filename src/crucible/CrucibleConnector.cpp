#include "../Debug.h"
#include "CrucibleConnector.h"
#include "RestCommunicator.h"
#include "Review.h"

#include <QSettings>

CrucibleConnector::CrucibleConnector( QObject *parent )
    : QObject(parent)
    , m_review(0)
{
    QSettings settings;

    m_server = settings.value("crucible/server", "http://stella:6060/foo").toString();
    m_user = settings.value("crucible/username", "matt").toString();
    m_password = settings.value("crucible/password", "matt").toString();
}

RestCommunicator * CrucibleConnector::createCommunicator() {
    RestCommunicator *communicator = new RestCommunicator(this);

    communicator->setServer(m_server);
    communicator->setUser(m_user);
    communicator->setPassword(m_password);

//    communicator->setServer("http://localhost:1234");

    return communicator;
}

void CrucibleConnector::createFailed(QNetworkReply *reply) {
    debug() << "Could not create review at" << m_server << ":" << reply->errorString();
}

void CrucibleConnector::createSuccessful(QNetworkReply *reply) {
    QString location = reply->header(QNetworkRequest::LocationHeader).toUrl().toString();
    QString url = reply->url().toString();

    QString id = location.remove(url).mid(1);
    m_review->setId(id);

    debug() << "id:" << id;
    QString reviewUrl = m_server + "/cru/" + id;

    qDebug() << "Created review:" << reviewUrl;

    if (m_review->shouldStart()) {
        startReview();
    }
    if (m_review->hasReviewers()) {
        addReviewers();
    }
}

void CrucibleConnector::createReview() {
    RestCommunicator *communicator = createCommunicator();

    connect(communicator, SIGNAL(callSuccessful(QNetworkReply*)),
            this, SLOT(createSuccessful(QNetworkReply*)));
    connect(communicator, SIGNAL(callFailed(QNetworkReply*)),
            this, SLOT(createFailed(QNetworkReply*)));

    communicator->postData(QString(), m_review->createData());
}

void CrucibleConnector::updateReview() {
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    RestCommunicator *communicator = createCommunicator();

    connect(communicator, SIGNAL(callSuccessful(QNetworkReply*)),
            this, SLOT(updateSuccessful(QNetworkReply*)));
    connect(communicator, SIGNAL(callFailed(QNetworkReply*)),
            this, SLOT(updateFailed(QNetworkReply*)));

    // First, add the changesets
//    communicator->postData(m_review->data(), m_review->id() + "/addChangeset");

    // Then, the patches
}

void CrucibleConnector::startReview() {
    DEBUG_BLOCK
    if (m_review->id().isEmpty()) {
        error() << "Can't start a review without a PermaId";
        return;
    }
    RestCommunicator *communicator = createCommunicator();

    connect(communicator, SIGNAL(callSuccessful(QNetworkReply*)),
            this, SLOT(startSuccessful(QNetworkReply*)));
    connect(communicator, SIGNAL(callFailed(QNetworkReply*)),
            this, SLOT(startFailed(QNetworkReply*)));

    communicator->post(m_review->id() + "/transition?action=action:approveReview");
}

void CrucibleConnector::startFailed(QNetworkReply *reply) {
    debug() << "Could not start review at" << m_server << ":" << reply->errorString();
}

void CrucibleConnector::startSuccessful(QNetworkReply *reply) {
    Q_UNUSED(reply);
    debug() << "review started";
}

void CrucibleConnector::addReviewers() {
    DEBUG_BLOCK
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    RestCommunicator *communicator = createCommunicator();

    connect(communicator, SIGNAL(callSuccessful(QNetworkReply*)),
            this, SLOT(reviewersSuccessful(QNetworkReply*)));
    connect(communicator, SIGNAL(callFailed(QNetworkReply*)),
            this, SLOT(reviewersFailed(QNetworkReply*)));

    communicator->postTextData(m_review->id() + "/reviewers", m_review->reviewers().join(","));
}

void CrucibleConnector::reviewersFailed(QNetworkReply *reply) {
    debug() << "Could not add reviewers at" << m_server << ":" << reply->errorString();
}

void CrucibleConnector::reviewersSuccessful(QNetworkReply *reply) {
    Q_UNUSED(reply);
    debug() << "reviewers added";
}

