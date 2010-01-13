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

#include "FishEyeChangesetWaitingAction.h"
#include "../../Review.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>
#include <QDomDocument>

FishEyeChangesetWaitingAction::FishEyeChangesetWaitingAction(Review *review, RestCommunicator *communicator, QObject *parent)
    : AbstractAction(communicator, parent)
    , m_changesets(review->changesets())
    , m_repository(review->repository())
    , m_attempts(0)
{
}

void FishEyeChangesetWaitingAction::run() {
    // TODO get all of the changesets
    m_attempts++;
    const QString cId = m_changesets.first();
    m_communicator->get(m_repository + "/" + cId);
}

void FishEyeChangesetWaitingAction::callFailed(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::ContentNotFoundError && m_attempts < MAX_ATTEMPTS) {
        debug() << "Couldn't find changeset, waiting...";
        run(); // try and try again.
    } else {
        debug() << "Could not find changeset at " << m_communicator->server().toString() << ":" << reply->errorString();
    }
}

void FishEyeChangesetWaitingAction::callSuccessful(QNetworkReply *reply) {
    if (!reply->bytesAvailable()) {
        return;
    }

    debug() << "Changeset found!";

    QByteArray data;
    while (reply->bytesAvailable()) {
        data.append(reply->readAll());
    }
    emit changesetFound();
}
