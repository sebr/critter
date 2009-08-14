#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>

class Project : public QObject
{
    public:
        Project(QObject *parent)
                : QObject(parent)
                , m_allowReviewersToJoin(false) {}

        QString name() const { return m_name; }
        void setName(const QString &name) { m_name = name; }

        QString id() const { return m_id; }
        void setId(const QString &id) { m_id = id; }

        QString key() const { return m_key; }
        void setKey(const QString &key) { m_key = key; }

        bool allowReviewersToJoin() const { return m_allowReviewersToJoin; }
        void setAllowReviewersToJoin(const bool allow) { m_allowReviewersToJoin = allow; }

    private:
        QString m_name;
        QString m_id;
        QString m_key;
        bool    m_allowReviewersToJoin;

};

#endif // PROJECT_H
