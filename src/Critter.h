#ifndef CRITTER_H
#define CRITTER_H

#include <QObject>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class CrucibleConnector;
class CrucibleConnectorBase;
class Review;

class Critter : public QObject
{
    Q_OBJECT

    public:
        Critter(QObject *parent = 0);
        Critter(CrucibleConnectorBase *connector, QObject *parent = 0);

        void setOptions(po::variables_map vm);

    public slots:
        void exec();

    private slots:
        void parseOptions();

    private:
        QByteArray loadPatch(const QString &filename) const;
        void readStdIn(Review *review);
        void testConnection();

        CrucibleConnector *m_crucibleConnector;
        po::variables_map m_vm;
};

#endif // CRITTER_H
