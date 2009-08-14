#include "LoadProjectsAction.h"
#include "../../Review.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>

void LoadProjectsAction::run() {
    m_communicator->get(QString());
}

void LoadProjectsAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not load projects from" << m_server << ":" << reply->errorString();
}

void LoadProjectsAction::callSuccessful(QNetworkReply *) {
    qDebug() << "Got projects";
    emit reviewStarted();
}
