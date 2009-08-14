#include "AddPatchesAction.h"
#include "../../Review.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>

void AddPatchesAction::run() {
    DEBUG_BLOCK

    m_patches.clear();
    foreach (const QByteArray ba, m_review->patches()) {
        m_patches.push_back(ba);
    }

    if (!m_patches.isEmpty()) {
        doPatchQueue();
    }
}

void AddPatchesAction::doPatchQueue() {
    if (m_patches.isEmpty()) {
        qDebug() << "Added" << m_review->patches().size() << "patches to" << m_review->id();
        emit patchesAdded();
        return;
    }
    const QByteArray patch = m_patches.pop();
    m_communicator->postData(m_review->id() + "/addPatch", m_review->patchData(patch));
}

void AddPatchesAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not add changesets to" << m_review->id() << ":" << reply->errorString();
}

void AddPatchesAction::callSuccessful(QNetworkReply *) {
    debug() << "added patch";
    doPatchQueue();
}
