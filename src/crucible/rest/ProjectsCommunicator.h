#ifndef PROJECTSCOMMUNICATOR_H
#define PROJECTSCOMMUNICATOR_H

#include "RestCommunicator.h"

class ProjectsCommunicator : public RestCommunicator
{
    public:
        ProjectsCommunicator(QObject *parent);

    protected:
        virtual QUrl apiUrl(const QString &path = QString()) const;
};

#endif // PROJECTSCOMMUNICATOR_H
