#ifndef ABSTRACTREVIEWACTION_H
#define ABSTRACTREVIEWACTION_H

#include "../../Review.h"
#include "../AbstractAction.h"

class AbstractReviewAction : public AbstractAction
{
    Q_OBJECT

    public:
        AbstractReviewAction(Review *review, RestCommunicator *communicator, QObject *parent)
            : AbstractAction(communicator, parent)
            , m_review(review) {}

    protected:
        Review *m_review;
};

#endif // ABSTRACTREVIEWACTION_H
