#include "AddChangesetsAction.h"
#include "../Review.h"
#include "../RestCommunicator.h"
#include "../../Debug.h"

#include <QNetworkReply>

void AddChangesetsAction::run() {
    m_communicator->postData(m_review->id() + "/addChangeset", m_review->changesetsData());
}

void AddChangesetsAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not add changesets to" << m_review->id() << ":" << reply->errorString();
}

void AddChangesetsAction::callSuccessful(QNetworkReply *) {
    qDebug() << "Added" << m_review->changesets().size() << "changesets to" << m_review->id();
    emit changesetsAdded();
}
