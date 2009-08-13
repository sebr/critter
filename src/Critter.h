#ifndef CRITTER_H
#define CRITTER_H

#include <QObject>

class CrucibleConnector;

class Critter : public QObject
{
    public:
        Critter(QObject *parent = 0);

        void readStdIn();
        void testConnection();

    private:
        CrucibleConnector *m_crucibleConnector;
};

#endif // CRITTER_H
