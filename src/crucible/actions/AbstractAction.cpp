
#include "AbstractAction.h"

#include "../rest/RestCommunicator.h"
#include "../../Debug.h"

#include <QNetworkReply>

AbstractAction::AbstractAction(const QUrl &server, RestCommunicator *communicator, QObject *parent)
    : QObject(parent)
    , m_server(server)
    , m_communicator(communicator)
{
    init();
}

void AbstractAction::init() {
    connect(m_communicator, SIGNAL(callSuccessful(QNetworkReply*)),
            this, SLOT(callSuccessfulSlot(QNetworkReply*)));
    connect(m_communicator, SIGNAL(callFailed(QNetworkReply*)),
            this, SLOT(callFailedSlot(QNetworkReply*)));
}

void AbstractAction::callFailedSlot(QNetworkReply *reply) {
    callFailed(reply);
}

void AbstractAction::callSuccessfulSlot(QNetworkReply *reply) {
    callSuccessful(reply);
}
