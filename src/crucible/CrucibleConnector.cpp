#include "../Debug.h"
#include "CrucibleConnector.h"
#include "RestCommunicator.h"
#include "Review.h"

#include <QSettings>

CrucibleConnector::CrucibleConnector( QObject *parent )
    : QObject( parent )
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
    debug() << "Could not create review:" << reply->errorString();
}

void CrucibleConnector::createSuccessful(QNetworkReply *reply) {
    QString location = reply->header(QNetworkRequest::LocationHeader).toUrl().toString();
    QString url = reply->url().toString();

    QString id = location.remove(url);

    QString reviewUrl = m_server + "/cru" + id;

    qDebug() << "Created review:" << reviewUrl;
}

bool CrucibleConnector::testConnection() const {
    return true;
}

void CrucibleConnector::createReview(const Review *review) {
    RestCommunicator *communicator = createCommunicator();

    connect(communicator, SIGNAL(callSuccessful(QNetworkReply*)),
            this, SLOT(createSuccessful(QNetworkReply*)));
    connect(communicator, SIGNAL(callFailed(QNetworkReply*)),
            this, SLOT(createFailed(QNetworkReply*)));

    communicator->postData(review->createData());
}

void CrucibleConnector::updateReview(const Review *review) {
    if (review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    RestCommunicator *communicator = createCommunicator();

    connect(communicator, SIGNAL(callSuccessful(QNetworkReply*)),
            this, SLOT(updateSuccessful(QNetworkReply*)));
    connect(communicator, SIGNAL(callFailed(QNetworkReply*)),
            this, SLOT(updateFailed(QNetworkReply*)));

    // First, add the changesets
//    communicator->postData(review->data(), review->id() + "/addChangeset");

    // Then, the patches
}

