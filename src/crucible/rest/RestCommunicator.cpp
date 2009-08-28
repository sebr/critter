#include "RestCommunicator.h"
#include "../../Debug.h"

#include <QAuthenticator>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlInputSource>

RestCommunicator::RestCommunicator(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinishedSlot(QNetworkReply*)));

    connect(m_manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));
}

void RestCommunicator::setServer( const QUrl &server )
{
    m_server = server;
}

void RestCommunicator::setUser( const QString &username )
{
    m_username = username;
}

void RestCommunicator::setPassword( const QString &password )
{
    m_password = password;
}

QUrl RestCommunicator::apiUrl(const QString &path) const {
    QUrl url(m_server.toString(QUrl::StripTrailingSlash) + "/rest-service/reviews-v1/" + path);
    return url;
}

void RestCommunicator::replyFinishedSlot(QNetworkReply *reply) {
    replyFinished(reply);
}

void RestCommunicator::replyFinished(QNetworkReply *reply) {
    if (reply->error()) {
        emit callFailed(reply);
    } else {
        emit callSuccessful(reply);
    }
}

bool RestCommunicator::testConnection()
{
    m_manager->get(QNetworkRequest(apiUrl()));
    return true;
}

void RestCommunicator::post(const QString &path) {
    postData(path);
}

void RestCommunicator::postTextData(const QString &path, const QString &data) {
    postData(path, data.toAscii());
}

void RestCommunicator::postData(const QString &path, const QByteArray &data, const QString &contentType) {
    QNetworkRequest request = authenticatedRequest(path, contentType);
    m_manager->post(request, data);
}

void RestCommunicator::get(const QString &path, const QString &contentType) {
    QNetworkRequest request = authenticatedRequest(path, contentType);
    m_manager->get(request);
}

QNetworkRequest RestCommunicator::authenticatedRequest(const QString &path, const QString &contentType) const {
    QNetworkRequest request(apiUrl(path));

    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QString auth(m_username + ":" + m_password);
    request.setRawHeader("Authorization", "Basic " + auth.toAscii().toBase64());
    return request;
}

void RestCommunicator::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator) {
    Q_UNUSED(reply);

    authenticator->setUser(m_username);
    authenticator->setPassword(m_password);
}

