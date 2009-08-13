#include "CrucibleConnector.h"
#include "RestCommunicator.h"
#include "Review.h"

#include <QSettings>

CrucibleConnector::CrucibleConnector( QObject *parent )
    : QObject( parent )
    , m_communicator( new RestCommunicator(this) )
{
    QSettings settings;

    m_communicator->setServer( settings.value("crucible/server", "http://stella:6060/foo").toString() );
    m_communicator->setUser( settings.value("crucible/username", "matt").toString() );
    m_communicator->setPassword( settings.value("crucible/password", "matt").toString() );
}

bool CrucibleConnector::testConnection() const {
    return m_communicator->testConnection();
}

void CrucibleConnector::createReview(const QString &user, const QString &project, const QString &name, const QString &description, const bool allowJoin) {

}
