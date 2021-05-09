#ifndef SEGMENT_H
#define SEGMENT_H
#include <QPoint>
#include <QVector>
#include "randgen.h"

class segment
{
    enum class pointCode : unsigned char {
        leftdown = 5
        , down = 4
        , rightdown = 6
        , left = 1
        , inwindow = 0
        , right = 2
        , leftup = 9
        , up = 8
        , rightup = 10
    };
    struct point {
        QPoint itself{};
        pointCode code = pointCode::inwindow;
        point(const QPoint &p) : itself(p) {}
    } start, end;

    const struct coefficients {
        qreal k, b;
        bool vertical = false;
    } coeff;

    QPoint leftdown{};
    QPoint rightup{};

    enum class visibility : int {
        fullyVisible
        ,unvisible
        ,partlyVisibleAInside
        ,partlyVisibleBInside
        ,partlyVisiblePointsOutside
    };

    coefficients straightCoefficients() const;
    void generateCodes();
    bool bothPointsOutside() const;
    pointCode getCode(const QPoint &p);
    void clipStartPoint();
    qreal xOfIntersection(qreal y);
    qreal yOfIntersection(qreal x);

    void errStop(const QString &msg);

public:
    segment(const QPoint &pa, const QPoint &pb);
    segment(RandomGenerator &gen);
    segment(RandomGenerator &xgen, RandomGenerator &ygen);

    void assertWindow(const QPoint &ld, const QPoint &ru);
    bool clip();
    QPair<QPoint, QPoint> result() const;
};

#endif // SEGMENT_H
