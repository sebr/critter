#ifndef REPOSTIORY_H
#define REPOSTIORY_H

#include <QObject>

class Repository : public QObject
{
    public:
        Repository(QObject *parent)
                : QObject(parent)
                , m_enabled(false) {}

        QString name() const { return m_name; }
        void setName(const QString &name) { m_name = name; }

        QString type() const { return m_type; }
        void setType(const QString &type) { m_type = type; }

        QString url() const { return m_url; }
        void setUrl(const QString &url) { m_url = url; }

        bool enabled() const { return m_enabled; }
        void setEnabled(const bool enabled) { m_enabled = enabled; }

    private:
        QString m_name;
        QString m_type;
        QString m_url;
        bool    m_enabled;

};

#endif // REPOSTIORY_H
