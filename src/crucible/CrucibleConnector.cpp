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

#include "../Debug.h"
#include "CrucibleConnector.h"
#include "rest/Communicators.h"
#include "Review.h"
#include "../Settings.h"
#include "dispatcher/SynchronousJobDispatcher.h"

#include "actions/reviews/AddChangesetsAction.h"
#include "actions/reviews/AddPatchesAction.h"
#include "actions/reviews/AddReviewersAction.h"
#include "actions/reviews/CreateReviewAction.h"
#include "actions/reviews/StartReviewAction.h"
#include "actions/fisheye/FishEyeChangesetWaitingAction.h"

#include <QQueue>

CrucibleConnector::CrucibleConnector(Settings *settings, QObject *parent)
    : CrucibleConnectorBase(settings, parent)
    , m_review(0)
{
}

void CrucibleConnector::createReview() {
    updateReviewContent(true);
}

void CrucibleConnector::updateReview() {
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    updateReviewContent();
}

void CrucibleConnector::updateReviewContent(bool createReview) {
    QQueue<AbstractAction*> actions;

    if (createReview) {
        actions.enqueue(new CreateReviewAction(m_review, createReviewsCommunicator(), this));
    }

    if (m_review->hasReviewers()) {
        actions.enqueue(new AddReviewersAction(m_review, createReviewsCommunicator(), this));
    }
    if (m_review->hasChangesets()) {
        actions.enqueue(new FishEyeChangesetWaitingAction(m_review->changesets(), createFishEyeCommunicator(), this));
        actions.enqueue(new AddChangesetsAction(m_review, createReviewsCommunicator(), this));
    }
    if (m_review->hasPatches()) {
        actions.enqueue(new AddPatchesAction(m_review, createReviewsCommunicator(), this));
    }
    if (m_review->shouldStart()) {
        actions.enqueue(new StartReviewAction(m_review, createReviewsCommunicator(), this));
    }

    SynchronousJobDispatcher *dispatcher = new SynchronousJobDispatcher(actions, this);
    connect(dispatcher, SIGNAL(finished()), this, SLOT(deleteLater()));
    dispatcher->execute();
}

FishEyeChangesetCommunicator* CrucibleConnector::createFishEyeCommunicator() {
    FishEyeChangesetCommunicator *fisheyeCommunicator = new FishEyeChangesetCommunicator(this);
    fisheyeCommunicator->setServer(server());
    fisheyeCommunicator->setUser(user());
    fisheyeCommunicator->setPassword(password());
    return fisheyeCommunicator;
}

ReviewsCommunicator* CrucibleConnector::createReviewsCommunicator() {
    ReviewsCommunicator *communicator = new ReviewsCommunicator(this);
    communicator->setServer(server());
    communicator->setUser(user());
    communicator->setPassword(password());
    return communicator;
}
