#include "SynchronousJobDispatcher.h"

#include "../actions/AbstractAction.h"

SynchronousJobDispatcher::SynchronousJobDispatcher(QQueue<AbstractAction*> actions, QObject *parent)
    : QObject(parent)
    , m_actions(actions)
{
}

void SynchronousJobDispatcher::execute() {
    AbstractAction *lastAction = dynamic_cast<AbstractAction*>(sender());
    if (lastAction) {
        disconnect(lastAction, SIGNAL(executed()), this, SLOT(execute()));
        if (!lastAction->successful()) {
            m_actions.clear();
            emit finished();
            return;
        }
    }

    if (m_actions.isEmpty()) {
        emit finished();
        return;
    }

    AbstractAction *action = m_actions.dequeue();
    connect(action, SIGNAL(executed()), this, SLOT(execute()));
    action->run();
}
