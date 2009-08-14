#include "RepositoryCommunicator.h"
#include "../../Debug.h"

RepositoryCommunicator::RepositoryCommunicator(QObject *parent)
    : RestCommunicator(parent)
{
}

QUrl RepositoryCommunicator::apiUrl(const QString &path) const {
    QUrl url(m_server.toString() + "/rest-service/repositories-v1/" + path);
    return url;
}
