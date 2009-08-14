#ifndef REVIEWSCOMMUNICATOR_H
#define REVIEWSCOMMUNICATOR_H

#include "RestCommunicator.h"

#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QXmlSimpleReader>

class QAuthenticator;
class QNetworkAccessManager;
class Review;

class ReviewsCommunicator : public RestCommunicator
{
    Q_OBJECT

    public:
        ReviewsCommunicator(QObject *parent);

    protected:
        virtual QUrl apiUrl(const QString &path = QString()) const;
};

#endif // REVIEWSCOMMUNICATOR_H
