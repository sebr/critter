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
