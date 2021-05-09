#ifndef SQUARE_H
#define SQUARE_H
#include <QPoint>
#include <QVector>
#include "segment.h"
#include <functional>

class square
{
    const QPoint leftdown{}, rightup{};
    std::function<void(QPair<QPoint, QPoint>)> drawSegment;

    void doSegment(segment &s) const;

public:
    square(const QPoint &p1, const QPoint &p2, std::function<void(QPair<QPoint, QPoint>)> drawSegmentFunction);
    void handleSegment(const QPair<QPoint, QPoint> &s) const;
};

#endif // SQUARE_H
