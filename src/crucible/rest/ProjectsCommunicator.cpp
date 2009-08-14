#include "ProjectsCommunicator.h"
#include "../../Debug.h"

ProjectsCommunicator::ProjectsCommunicator(QObject *parent)
    : RestCommunicator(parent)
{
}

QUrl ProjectsCommunicator::apiUrl(const QString &path) const
