#include "Review.h"

#include <QXmlStreamWriter>

Review::Review(QObject *parent)
    : QObject(parent)
    , m_allowReviewersToJoin(true)
{
}


QByteArray Review::createData() const {
    QByteArray ba;

    QXmlStreamWriter xml(&ba);
    xml.writeStartDocument();
    xml.writeStartElement("createReview");

    xml.writeStartElement("reviewData");

    xml.writeTextElement("allowReviewersToJoin", m_allowReviewersToJoin ? "true" : "false");

    xml.writeStartElement("author");
    xml.writeTextElement("userName", m_author);
    xml.writeEndElement();

    xml.writeStartElement("creator");
    xml.writeTextElement("userName", m_creator.isEmpty() ? m_author : m_creator);
    xml.writeEndElement();

    xml.writeStartElement("moderator");
    xml.writeTextElement("userName", m_moderator.isEmpty() ? m_author : m_moderator);
    xml.writeEndElement();

    if (!m_description.isEmpty()) {
        xml.writeTextElement("description", m_description);
    }

    xml.writeTextElement("name", m_name);
    xml.writeTextElement("projectKey", m_project);

    xml.writeEndElement(); // reviewData

    xml.writeStartElement("changesets");
    xml.writeTextElement("repository", m_repository);
    foreach(const QString cs, m_changesets) {
        xml.writeStartElement("changesetData");
        xml.writeTextElement("id", cs);
        xml.writeEndElement();
    }
    xml.writeEndElement(); // changesets

    xml.writeEndElement(); // createReview
    xml.writeEndDocument();

    return ba;
}
