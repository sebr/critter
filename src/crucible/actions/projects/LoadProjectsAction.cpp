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

#include "LoadProjectsAction.h"
#include "../../Project.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>
#include <QDomDocument>

void LoadProjectsAction::run() {
    m_communicator->get(QString());
}

void LoadProjectsAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not load projects from" << m_communicator->server().toString() << ":" << reply->errorString();
}

void LoadProjectsAction::callSuccessful(QNetworkReply *reply) {
    if (!reply->bytesAvailable()) {
        return;
    }

    QByteArray data;
    while (reply->bytesAvailable()) {
        data.append(reply->readAll());
    }

    QList<Project*> projects;

    QDomDocument doc;
    doc.setContent(data);

    QDomNodeList nodeList = doc.elementsByTagName("projectData");
    for (uint i = 0; i < nodeList.length(); ++i) {
        QDomNode node = nodeList.at(i);
        Project *project = new Project(this);
        for (uint j = 0; j < node.childNodes().length(); ++j) {
            QDomElement child = node.childNodes().at(j).toElement();
            QString name = child.tagName();
            QString value = child.text();
            if (name == "allowReviewersToJoin") {
                project->setAllowReviewersToJoin(value == "true");
            } else if (name == "id") {
                project->setId(value);
            } else if (name == "key") {
                project->setKey(value);
            } else if (name == "name") {
                project->setName(value);
            }
        }
        projects.append(project);
    }

    emit projectsReceived(projects);
}
