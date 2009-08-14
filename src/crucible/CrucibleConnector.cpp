#include "../Debug.h"
#include "CrucibleConnector.h"
#include "rest/ReviewsCommunicator.h"
#include "Review.h"

#include "actions/reviews/AddChangesetsAction.h"
#include "actions/reviews/AddPatchesAction.h"
#include "actions/reviews/AddReviewersAction.h"
#include "actions/reviews/CreateReviewAction.h"
#include "actions/reviews/StartReviewAction.h"

#include <QSettings>

CrucibleConnector::CrucibleConnector( QObject *parent )
    : QObject(parent)
    , m_review(0)
{
    QSettings settings;

    setServer( settings.value("crucible/server", "http://stella:6060/foo").toString() );
    m_user = settings.value("crucible/username", "matt").toString();
    m_password = settings.value("crucible/password", "matt").toString();
}

void CrucibleConnector::setServer(const QString &server) {
    m_server = QUrl(server);
    if (m_server.scheme().isEmpty()) {
        m_server.setScheme("http");
    }
}

RestCommunicator * CrucibleConnector::createCommunicator() {
    RestCommunicator *communicator = new ReviewsCommunicator(this);

    communicator->setServer(m_server);
    communicator->setUser(m_user);
    communicator->setPassword(m_password);

    return communicator;
}

void CrucibleConnector::updateReviewContent() {
    DEBUG_BLOCK
    if (m_review->shouldStart()) {
        startReview();
    }
    if (m_review->hasReviewers()) {
        addReviewers();
    }
//    if (m_review->hasUploads()) {
//        addUploads();
//    }
    if (m_review->hasChangesets()) {
        addChangesets();
    }
    if (m_review->hasPatches()) {
        addPatches();
    }
}

void CrucibleConnector::createReview() {
    DEBUG_BLOCK
    CreateReviewAction *a = new CreateReviewAction(m_server, m_review, createCommunicator(), this);

    connect(a, SIGNAL(reviewCreated()), this, SLOT(updateReviewContent()));

    a->run();
}

void CrucibleConnector::updateReview() {
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }

    updateReviewContent();
}

void CrucibleConnector::startReview() {
    if (m_review->id().isEmpty()) {
        error() << "Can't start a review without a PermaId";
        return;
    }
    StartReviewAction *a = new StartReviewAction(m_server, m_review, createCommunicator(), this);
    a->run();
}

void CrucibleConnector::addReviewers() {
    DEBUG_BLOCK
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    AddReviewersAction *a = new AddReviewersAction(m_server, m_review, createCommunicator(), this);
    a->run();
}

void CrucibleConnector::addChangesets() {
    DEBUG_BLOCK
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    AddChangesetsAction *a = new AddChangesetsAction(m_server, m_review, createCommunicator(), this);
    a->run();
}

void CrucibleConnector::addPatches() {
    DEBUG_BLOCK
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    AddPatchesAction *a = new AddPatchesAction(m_server, m_review, createCommunicator(), this);
    a->run();
}





