#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    public:
        User(QObject *parent)
                : QObject(parent)
                {}

        QString userName() const { return m_userName; }
        void setUserName(const QString &name) { m_userName = name; }

        QString displayName() const { return m_displayName; }
        void setDisplayName(const QString &name) { m_displayName = name; }

    private:
        QString m_userName;
        QString m_displayName;
};


#endif // USER_H
