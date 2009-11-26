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

#include "actions/reviews/AddChangesetsAction.h"
#include "actions/reviews/AddPatchesAction.h"
#include "actions/reviews/AddReviewersAction.h"
#include "actions/reviews/CreateReviewAction.h"
#include "actions/reviews/StartReviewAction.h"
#include "actions/fisheye/FishEyeChangesetWaitingAction.h"

CrucibleConnector::CrucibleConnector(Settings *settings, QObject *parent)
    : CrucibleConnectorBase(settings, parent)
    , m_review(0)
{
}

void CrucibleConnector::updateReviewContent() {
    ReviewsCommunicator *communicator = new ReviewsCommunicator(this);
    communicator->setServer(server());
    communicator->setUser(user());
    communicator->setPassword(password());

    if (m_review->hasReviewers()) {
        m_actions.enqueue(new AddReviewersAction(m_review, communicator, this));
    }
    if (m_review->hasChangesets()) {
        FishEyeChangesetCommunicator *fisheyeCommunicator = new FishEyeChangesetCommunicator(this);
        fisheyeCommunicator->setServer(server());
        fisheyeCommunicator->setUser(user());
        fisheyeCommunicator->setPassword(password());

        m_actions.enqueue(new FishEyeChangesetWaitingAction(m_review->changesets(), fisheyeCommunicator, this));
        m_actions.enqueue(new AddChangesetsAction(m_review, communicator, this));
    }
    if (m_review->hasPatches()) {
        m_actions.enqueue(new AddPatchesAction(m_review, communicator, this));
    }
    if (m_review->shouldStart()) {
        m_actions.enqueue(new StartReviewAction(m_review, communicator, this));
    }

    doActions();
}

void CrucibleConnector::createReview() {
    ReviewsCommunicator *communicator = new ReviewsCommunicator(this);
    communicator->setServer(server());
    communicator->setUser(user());
    communicator->setPassword(password());

    CreateReviewAction *a = new CreateReviewAction(m_review, communicator, this);
    connect(a, SIGNAL(reviewCreated()), this, SLOT(updateReviewContent()));
    a->run();
}

void CrucibleConnector::updateReview() {
    if (m_review->id().isEmpty()) {
        error() << "Can't update a review without a PermaId";
        return;
    }
    updateReviewContent();
}

void CrucibleConnector::doActions() {
    AbstractAction *lastAction = dynamic_cast<AbstractAction*>(sender());
    if (lastAction) {
        disconnect(lastAction, SIGNAL(executed()), this, SLOT(doActions()));
    }

    if (m_actions.isEmpty()) {
        m_isExecuting = false;
        emit finished();
        return;
    }

    m_isExecuting = true;

    AbstractAction *action = m_actions.dequeue();
    connect(action, SIGNAL(executed()), this, SLOT(doActions()));
    action->run();
}

