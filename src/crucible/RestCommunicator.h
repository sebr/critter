#ifndef RESTCOMMUNICATOR_H
#define RESTCOMMUNICATOR_H

#include <QNetworkReply>
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

    signals:
        void callFailed(QNetworkReply*);
        void callSuccessful(QNetworkReply*);

    private slots:
        void replyFinished(QNetworkReply *reply);
        void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);

    private:
        inline QUrl apiUrl(const QString &path = QString()) const;
        inline QUrl feApiUrl(const QString &path = QString()) const;

        QNetworkAccessManager *m_manager;
        QUrl m_server;
        QString m_username;
        QString m_password;
};

#endif // RESTCOMMUNICATOR_H
