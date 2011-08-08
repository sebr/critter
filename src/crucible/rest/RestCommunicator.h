/****************************************************************************
 **
 ** Copyright (c) 2009, Seb Ruiz <sruiz@atlassian.com>
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 **
 ** Redistributions of source code must retain the above copyright notice, this
 ** list of conditions and the following disclaimer. Redistributions in binary
 ** form must reproduce the above copyright notice, this list of conditions and
 ** the following disclaimer in the documentation and/or other materials provided
 ** with the distribution.
 **
 ** Neither Atlassian nor the names of its contributors may be used to endorse or
 ** promote products derived from this software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 ** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 ** INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 ** BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 ** OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 ** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 ** OF SUCH DAMAGE.
 **
 ****************************************************************************/

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

        void get(const QString &path, const QString &contentType = "application/xml");

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
