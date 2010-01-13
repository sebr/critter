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

#include "CreateReviewAction.h"
#include "../../Review.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>

void CreateReviewAction::run() {
    debug() << "Creating review...";
    m_communicator->postData(QString(), m_review->createData());
}

void CreateReviewAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not create review at" << m_communicator->server().toString(QUrl::RemoveUserInfo) << ":" << reply->errorString();
}

void CreateReviewAction::callSuccessful(QNetworkReply *reply) {
    QString location = reply->header(QNetworkRequest::LocationHeader).toUrl().toString();
    QString url = reply->url().toString();

    QString id = location.remove(url).mid(1);
    m_review->setId(id);

    QString reviewUrl = m_communicator->server().toString(QUrl::StripTrailingSlash) + "/cru/" + id;

    qDebug() << "Created review:" << reviewUrl;

    emit reviewCreated();
}
