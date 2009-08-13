#ifndef CRUCIBLECONNECTOR_H
#define CRUCIBLECONNECTOR_H

#include <QObject>

class RestCommunicator;

class CrucibleConnector : public QObject
{
    public:
        CrucibleConnector( QObject *parent );

        bool testConnection() const;

        void createReview(const QString &user, const QString &project, const QString &name, const QString &description, const bool allowJoin);

    private:
        RestCommunicator *m_communicator;
};

#endif // CRUCIBLECONNECTOR_H
