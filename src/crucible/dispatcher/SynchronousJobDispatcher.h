#ifndef SYNCHRONOUSJOBDISPATCHER_H
#define SYNCHRONOUSJOBDISPATCHER_H

#include <QObject>
#include <QQueue>

class AbstractAction;

class SynchronousJobDispatcher : public QObject
{
        Q_OBJECT

    public:
        explicit SynchronousJobDispatcher(QQueue<AbstractAction*> actions, QObject *parent = 0);

    signals:
        void finished();

    public slots:
        void execute();

    public:
        QQueue<AbstractAction*> m_actions;
};

#endif // SYNCHRONOUSJOBDISPATCHER_H
