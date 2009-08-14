#ifndef COMMUNICATORS_H
#define COMMUNICATORS_H

#include "RestCommunicator.h"

#include <QUrl>

class ProjectsCommunicator : public RestCommunicator
{
    public:
        ProjectsCommunicator(QObject *parent) : RestCommunicator(parent) {}

    protected:
        virtual QUrl apiUrl(const QString &path = QString()) const {
            return QUrl(m_server.toString(QUrl::StripTrailingSlash) + "/rest-service/projects-v1/" + path);
        }
};

class RepositoryCommunicator : public RestCommunicator
{
    public:
        RepositoryCommunicator(QObject *parent) : RestCommunicator(parent) {}

    protected:
        virtual QUrl apiUrl(const QString &path = QString()) const {
            return QUrl(m_server.toString(QUrl::StripTrailingSlash) + "/rest-service/repositories-v1/" + path);
        }
};

class ReviewsCommunicator : public RestCommunicator
{
    Q_OBJECT

    public:
        ReviewsCommunicator(QObject *parent) : RestCommunicator(parent) {}

    protected:
        virtual QUrl apiUrl(const QString &path = QString()) const {
            return QUrl(m_server.toString(QUrl::StripTrailingSlash) + "/rest-service/reviews-v1/" + path);
        }
};

class UsersCommunicator : public RestCommunicator
{
    Q_OBJECT

    public:
        UsersCommunicator(QObject *parent) : RestCommunicator(parent) {}

    protected:
        virtual QUrl apiUrl(const QString &path = QString()) const {
            return QUrl(m_server.toString(QUrl::StripTrailingSlash) + "/rest-service/users-v1/" + path);
        }
};


#endif // COMMUNICATORS_H
