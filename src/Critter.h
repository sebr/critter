#ifndef CRITTER_H
#define CRITTER_H

#include <QObject>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class CrucibleConnector;

class Critter : public QObject
{
    public:
        Critter(QObject *parent = 0);

        void parseOptions(po::variables_map vm);

    private:
        QByteArray loadPatch(const QString &filename) const;
        void readStdIn();
        void testConnection();

        CrucibleConnector *m_crucibleConnector;
};

#endif // CRITTER_H
