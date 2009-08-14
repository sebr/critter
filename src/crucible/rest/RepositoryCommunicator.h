#ifndef REPOSITORYCOMMUNICATOR_H
#define REPOSITORYCOMMUNICATOR_H

#include "RestCommunicator.h"

class RepositoryCommunicator : public RestCommunicator
{
    public:
        RepositoryCommunicator(QObject *parent);

    protected:
        virtual QUrl apiUrl(const QString &path = QString()) const;
};

#endif // REPOSITORYCOMMUNICATOR_H
