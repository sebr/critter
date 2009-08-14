#ifndef RESTCOMMUNICATOR_H
#define RESTCOMMUNICATOR_H

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
#include <QXmlSimpleReader>

class QAuthenticator;
class QNetworkAccessManager;
class Review;

class RestCommunicator : public QObject
{
    Q_OBJECT

    public:
        RestCommunicator(QObject *parent);
        virtual ~RestCommunicator() {}

        QUrl server() const { return m_server; }
        void setServer( const QUrl &server );
        void setUser( const QString &username );
        void setPassword( const QString &password );

        bool testConnection();

        void post(const QString &path);
        void postTextData(const QString &path, const QString &data);
        void postData(const QString &path, const QByteArray &data = QByteArray(), const QString &contentType = "application/xml");

        void get(const QString &path);

    signals:
        void callFailed(QNetworkReply*);
        void callSuccessful(QNetworkReply*);

    protected slots:
        void replyFinishedSlot(QNetworkReply *reply);
        void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);

    protected:
        virtual QNetworkRequest authenticatedRequest(const QString &path, const QString &contentType = QString()) const;
        virtual void replyFinished(QNetworkReply *reply);
        virtual QUrl apiUrl(const QString &path = QString()) const = 0;

        QNetworkAccessManager *m_manager;
        QUrl m_server;
        QString m_username;
        QString m_password;
};

#endif // RESTCOMMUNICATOR_H
