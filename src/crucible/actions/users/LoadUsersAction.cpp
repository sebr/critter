#include "LoadUsersAction.h"

#include "LoadUsersAction.h"
#include "../../User.h"
#include "../../rest/RestCommunicator.h"
#include "../../../Debug.h"

#include <QNetworkReply>
#include <QDomDocument>

void LoadUsersAction::run() {
    m_communicator->get(QString());
}

void LoadUsersAction::callFailed(QNetworkReply *reply) {
    debug() << "Could not load projects from" << m_communicator->server().toString() << ":" << reply->errorString();
}

void LoadUsersAction::callSuccessful(QNetworkReply *reply) {
    if (!reply->bytesAvailable()) {
        return;
    }

    QByteArray data;
    while (reply->bytesAvailable()) {
        data.append(reply->readAll());
    }

    QList<User*> users;

    QDomDocument doc;
    doc.setContent(data);

    QDomNodeList nodeList = doc.elementsByTagName("userData");
    for (uint i = 0; i < nodeList.length(); ++i) {
        QDomNode node = nodeList.at(i);
        User *user = new User(this);
        for (uint j = 0; j < node.childNodes().length(); ++j) {
            QDomElement child = node.childNodes().at(j).toElement();
            QString name = child.tagName();
            QString value = child.text();
            if (name == "displayName") {
                user->setDisplayName(value);
            } else if (name == "userName") {
                user->setUserName(value);
            }
        }
        users.append(user);
    }

    emit usersReceived(users);
}

