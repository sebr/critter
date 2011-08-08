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

#ifndef REVIEW_H
#define REVIEW_H

#include <QByteArray>
#include <QObject>
#include <QStringList>

class Review : public QObject
{
    public:
        Review(QObject *parent);

        QByteArray createData() const;
        QByteArray patchData(const QByteArray &patch) const;
        QByteArray changesetsData() const;
        QByteArray uploadData(const QByteArray &upload) const;

        QString id() const { return m_id; }
        void setId(const QString &id) { m_id = id; }

        QString project() const { return m_project; }
        void setProject(const QString &project) { m_project = project; }

        QString name() const { return m_name; }
        void setName(const QString &name) { m_name = name; }

        QString description() const { return m_description; }
        void setDescription(const QString &description) { m_description = description; }

        bool allowReviewersToJoin() const { return m_allowReviewersToJoin; }
        void setAllowReviewersToJoin(const bool allow) { m_allowReviewersToJoin = allow; }

        bool shouldStart() const { return m_shouldStart; }
        void setShouldStart(const bool start) { m_shouldStart = start; }

        QString author() const { return m_author; }
        void setAuthor(const QString &author) { m_author = author; }

        QString moderator() const { return m_moderator; }
        void setModerator(const QString &moderator) { m_moderator = moderator; }

        QString creator() const { return m_creator; }
        void setCreator(const QString &creator) { m_creator = creator; }

        QString repository() const { return m_repository; }
        void setRepository(const QString &repository) { m_repository = repository; }

        QStringList reviewers() const { return m_reviewers; }
        void addReviewer(const QString &reviewer) { m_reviewers << reviewer; }
        bool hasReviewers() const { return !m_reviewers.isEmpty(); }

        QStringList changesets() const { return m_changesets; }
        void addChangeset(const QString &cs) { m_changesets << cs; }
        bool hasChangesets() const { return !m_changesets.isEmpty(); }

        QList<QByteArray> patches() const { return m_patches; }
        void addPatch(const QByteArray &data) { m_patches << data; }
        bool hasPatches() const { return !m_patches.isEmpty(); }

        QList<QByteArray> uploads() const { return m_uploads; }
        void addUpload(const QByteArray &data) { m_uploads << data; }
        bool hasUploads() const { return !m_uploads.isEmpty(); }

        QByteArray snippetData() const { return m_snippetData; }
        void setSnippetData(const QByteArray &data) { m_snippetData = data; }

        QString snippetFilename() const { return m_snippetFilename; }
        void setSnippetFilename(const QString &name) { m_snippetFilename = name; }

        bool isSnippet() const { return m_isSnippet; }
        void setSnippet(const bool s) { m_isSnippet = s; }


    private:
        QString m_id;
        QString m_project;

        QString m_name;
        QString m_description;
        bool    m_allowReviewersToJoin;
        bool    m_shouldStart;

        QString m_author;
        QString m_moderator;
        QString m_creator;

        QString           m_repository;
        QStringList       m_reviewers;
        QStringList       m_changesets;
        QList<QByteArray> m_patches;
        QList<QByteArray> m_uploads;

        bool              m_isSnippet;
        QString           m_snippetFilename;
        QByteArray        m_snippetData;
};

#endif // REVIEW_H
