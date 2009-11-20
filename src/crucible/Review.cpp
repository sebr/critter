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

    xml.writeEndElement(); // createReview
    xml.writeEndDocument();

    return ba;
}

QByteArray Review::patchData(const QByteArray &patch) const {
    QByteArray ba;

    QXmlStreamWriter xml(&ba);
    xml.writeStartDocument();

    xml.writeStartElement("addPatch");

    xml.writeTextElement("repository", m_repository);
    xml.writeStartElement("patch");
    xml.writeCDATA(patch);
    xml.writeEndElement();

    xml.writeEndElement();

    xml.writeEndDocument();

    return ba;
}

QByteArray Review::changesetsData() const {
    QByteArray ba;

    QXmlStreamWriter xml(&ba);
    xml.writeStartDocument();

    xml.writeStartElement("addChangeset");

    xml.writeTextElement("repository", m_repository);
    xml.writeStartElement("changesets");
    foreach(const QString cs, m_changesets) {
        xml.writeStartElement("changesetData");
        xml.writeTextElement("id", cs);
        xml.writeEndElement();
    }
    xml.writeEndElement(); // changesets

    xml.writeEndElement();

    xml.writeEndDocument();

    return ba;
}

QByteArray Review::uploadData(const QByteArray &upload) const {
    Q_UNUSED(upload);

    QByteArray ba;
    return ba;
}
