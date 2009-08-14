#ifndef CRUCIBLECONNECTORBASE_H
#define CRUCIBLECONNECTORBASE_H

#include <QObject>
#include <QSettings>
#include <QUrl>

class CrucibleConnectorBase : public QObject
{
    Q_OBJECT

    public:
        CrucibleConnectorBase(QObject *parent = 0)
            : QObject(parent)
        {
            QSettings settings;

            setServer( settings.value("crucible/server", "http://stella:6060/foo").toString() );
            m_user = settings.value("crucible/username", "matt").toString();
            m_password = settings.value("crucible/password", "matt").toString();
        }

        void setServer(const QString &server) {
            m_server = QUrl(server);
            if (m_server.scheme().isEmpty()) {
                m_server.setScheme("http");
            }
        }

        QUrl server() const { return m_server; }

    protected:
        QUrl m_server;
        QString m_user;
        QString m_password;
};

#endif // CRUCIBLECONNECTORBASE_H
