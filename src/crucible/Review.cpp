#include "Review.h"

Review::Review(QObject *parent)
    : QObject(parent)
    , m_allowReviewersToJoin(true)
{
}
