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
