#ifndef RESTCOMMUNICATOR_H
#define RESTCOMMUNICATOR_H

#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QXmlSimpleReader>

class QAuthenticator;
class QNetworkAccessManager;


class RestCommunicator : public QObject
{
    Q_OBJECT

    public:
        RestCommunicator(QObject *parent);
        virtual ~RestCommunicator() {}

        void setServer( const QString &server );
        void setUser( const QString &username );
        void setPassword( const QString &password );

        bool testConnection();

        void postData(const QByteArray &data, const QString &path);

    signals:
//        void xmlError(QXmlSimpleReader);
//        void xmlReceived(QXmlSimpleReader);
        void callFailed(QNetworkReply::NetworkError);
        void callSuccessful();

    private slots:
        void replyFinished(QNetworkReply *reply);
        void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);

    private:
        inline QUrl apiUrl(const QString &path = QString()) const;

        QNetworkAccessManager *m_manager;
        QString m_server;
        QString m_username;
        QString m_password;
};

#endif // RESTCOMMUNICATOR_H
