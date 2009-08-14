#include "ProjectsCommunicator.h"
#include "../../Debug.h"

#include <QNetworkReply>

ProjectsCommunicator::ProjectsCommunicator(QObject *parent)
    : RestCommunicator(parent)
{
}

QUrl ProjectsCommunicator::apiUrl(const QString &path) const {
    QUrl url(m_server.toString(QUrl::StripTrailingSlash) + "/rest-service/projects-v1/" + path);
    return url;
}
