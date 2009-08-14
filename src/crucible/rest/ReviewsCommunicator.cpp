#include "ReviewsCommunicator.h"
#include "../../Debug.h"

ReviewsCommunicator::ReviewsCommunicator(QObject *parent)
    : RestCommunicator(parent)
{
}

QUrl ReviewsCommunicator::apiUrl(const QString &path) const {
    QUrl url(m_server.toString(QUrl::StripTrailingSlash) + "/rest-service/reviews-v1/" + path);
    return url;
}
