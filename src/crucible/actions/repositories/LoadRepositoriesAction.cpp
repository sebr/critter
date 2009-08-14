#include "LoadRepositoriesAction.h"

#include "../../Repository.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>
#include <QDomDocument>

void LoadRepositoriesAction::run() {
    m_communicator->get(QString());
}

void LoadRepositoriesAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not load repositories from" << m_communicator->server().toString() << ":" << reply->errorString();
}

void LoadRepositoriesAction::callSuccessful(QNetworkReply *reply) {

    if (!reply->bytesAvailable()) {
        return;
    }

    QByteArray data;
    while (reply->bytesAvailable()) {
        data.append(reply->readAll());
    }

    QList<Repository*> repos;

    QDomDocument doc;

    debug() << data;

    doc.setContent(data);
    QDomNodeList nodeList = doc.elementsByTagName("repoData");
    for (uint i = 0; i < nodeList.length(); ++i) {
        QDomNode node = nodeList.at(i);
        Repository *repo = new Repository(this);
        for (uint j = 0; j < node.childNodes().length(); ++j) {
            QDomElement child = node.childNodes().at(j).toElement();
            QString name = child.tagName();
            QString value = child.text();
            if (name == "enabled") {
                repo->setEnabled(value == "true");
            } else if (name == "type") {
                repo->setType(value);
            } else if (name == "url") {
                repo->setUrl(value);
            } else if (name == "name") {
                repo->setName(value);
            }
        }
        repos.append(repo);
    }

    emit repositoriesReceived(repos);
}

