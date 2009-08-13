#ifndef REVIEW_H
#define REVIEW_H

#include <QObject>

class Review : public QObject
{
    public:
        Review(QObject *parent);

        QString name() const { return m_name; }
        void setName(const QString &name) { m_name = name; }

        QString description() const { return m_description; }
        void setDescription(const QString &description) { m_description = description; }

        bool allowReviewersToJoin() const { return m_allowReviewersToJoin; }
        void setAllowReviewersToJoin(const bool allow) { m_allowReviewersToJoin = allow; }

        QString author() const { return m_author; }
        void setAuthor(const QString &author) { m_author = author; }

        QString moderator() const { return m_moderator; }
        void setModerator(const QString &moderator) { m_moderator = moderator; }

        QString creator() const { return m_creator; }
        void setCreator(const QString &creator) { m_creator = creator; }

        QList<QString> reviewers() const { return m_reviewers; }
        void addReviewer(const QString &reviewer) { m_reviewers << reviewer; }

        QList<QByteArray> patches() const { return m_patches; }
        void addPatch(const QByteArray &data) { m_patches << data; }

        QList<QByteArray> uploads() const { return m_uploads; }
        void addUpload(const QByteArray &data) { m_uploads << data; }

    private:
        QString m_name;
        QString m_description;
        bool    m_allowReviewersToJoin;

        QString m_author;
        QString m_moderator;
        QString m_creator;

        QList<QString>    m_reviewers;
        QList<QByteArray> m_patches;
        QList<QByteArray> m_uploads;
};

#endif // REVIEW_H
