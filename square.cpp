#include "square.h"


square::square(const QPoint &p1, const QPoint &p2, std::function<void (QPair<QPoint, QPoint>)> drawSegmentFunction)
    : leftdown(qMin(p1.x(), p2.x()), qMin(p1.y(), p2.y()))
    , rightup(qMax(p1.x(), p2.x()), qMax(p1.y(), p2.y()))
    , drawSegment(drawSegmentFunction)
{}

void square::handleSegment(const QPair<QPoint, QPoint> &s) const
{
    segment sg(s.first, s.second);
    doSegment(sg);
}

void square::doSegment(segment &s) const
{
    s.assertWindow(leftdown, rightup);
    if (s.clip()) {
        drawSegment(s.result());
    }
}
