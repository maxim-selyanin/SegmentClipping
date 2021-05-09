#include "segment.h"
#include <QDebug>

segment::segment(const QPoint &pa, const QPoint &pb)
    : start(pa)
    , end(pb)
    , coeff(straightCoefficients())
{}

segment::segment(RandomGenerator &gen)
    : start(QPoint(gen(), gen()))
    , end(QPoint(gen(), gen()))
    , coeff(straightCoefficients())
{}

segment::segment(RandomGenerator &xgen, RandomGenerator &ygen)
    : start(QPoint(xgen(), ygen()))
    , end(QPoint(xgen(), ygen()))
    , coeff(straightCoefficients())
{}

qreal segment::xOfIntersection(qreal y)
{
    if (coeff.vertical) {//вертикальная прямая
        return coeff.k;//возвращаем х, который в таком случае лежит в коэффициенте k
    }
    if (coeff.k == 0) {//горизонтальная прямая
        errStop("пересечение горизональных линий");
    }
    return (y - coeff.b)/coeff.k;
}

qreal segment::yOfIntersection(qreal x)
{
    if (coeff.vertical) {
        errStop("пересечение вертикальных линий");
    }
    return coeff.k*x + coeff.b;
}

void segment::errStop(const QString &msg)
{
    start = end;
    qDebug() << msg;
}

void segment::assertWindow(const QPoint &ld, const QPoint &ru)
{
    leftdown = ld;
    rightup = ru;
    generateCodes();
}

bool segment::clip()
{
    //тривиальные случаи
    if (bothPointsOutside()) {
        return false;
    } else if (start.code == pointCode::inwindow && end.code == pointCode::inwindow) {
        return true;
    }

    //нетривиальный случай
    if (start.code == pointCode::inwindow) {//начальная точка должна быть вне окна
        std::swap(start, end);
    }

    //start за пределами окна
    clipStartPoint();
    //вызываем clip для укороченного отрезка
    return clip();
}

QPair<QPoint, QPoint> segment::result() const
{
    return qMakePair(start.itself, end.itself);
}

void segment::generateCodes()
{
    start.code = getCode(start.itself);
    end.code = getCode(end.itself);
}

bool segment::bothPointsOutside() const
{
    unsigned char a = static_cast<unsigned char>(start.code);
    unsigned char b = static_cast<unsigned char>(end.code);
    return a & b;
}

segment::pointCode segment::getCode(const QPoint &p)
{
    if (p.y() < leftdown.y()) {//ниже окна
        if (p.x() < leftdown.x()) {//левее окна
            return pointCode::leftdown;
        } else if (p.x() >= leftdown.x() && p.x() <= rightup.x()) {//в окне по х
            return pointCode::down;
        } else {//правее окна
            return pointCode::rightdown;
        }
    } else if (p.y() >= leftdown.y() && p.y() <= rightup.y()) {//в окне по у
        if (p.x() < leftdown.x()) {//левее окна
            return pointCode::left;
        } else if (p.x() >= leftdown.x() && p.x() <= rightup.x()) {//в окне по х
            return pointCode::inwindow;
        } else {//правее окна
            return pointCode::right;
        }
    } else {//выше окна
        if (p.x() < leftdown.x()) {//левее окна
            return pointCode::leftup;
        } else if (p.x() >= leftdown.x() && p.x() <= rightup.x()) {//в окне по х
            return pointCode::up;
        } else {//правее окна
            return pointCode::rightup;
        }
    }
}

void segment::clipStartPoint()
{
    switch (start.code) {
    case pointCode::inwindow : {
        errStop("этого не может быть!");
        return;
    }
    case pointCode::leftup:
    case pointCode::left:
    case pointCode::leftdown: {
        //ищем пересечение по y с левой вертикальной границей
        start.itself = QPoint(leftdown.x(), yOfIntersection(leftdown.x()));
        break;
    }
    case pointCode::up: {
        //ищем пересечение по х с верхней горизонтальной границей
        start.itself = QPoint(xOfIntersection(rightup.y()), rightup.y());
        break;
    }
    case pointCode::rightup:
    case pointCode::right:
    case pointCode::rightdown: {
        //ищём пересечение по у с правой вертикальной границей
        start.itself = QPoint(rightup.x(), yOfIntersection(rightup.x()));
        break;
    }
    case pointCode::down: {
        //ищём пересечение по х с нижней горизонтальной границей
        start.itself = QPoint(xOfIntersection(leftdown.y()), leftdown.y());
        break;
    }
    }
    start.code = getCode(start.itself);
}

segment::coefficients segment::straightCoefficients() const
{
    //вертикальная прямая
    if (start.itself.x() == end.itself.x()) {
        return coefficients{(qreal)start.itself.x(),//сохраняем коэффициент x
                    (qreal)start.itself.x(),
                    true};
    }

    //координаты точек в даблах
    qreal ax = start.itself.x();
    qreal ay = start.itself.y();
    qreal bx = end.itself.x();
    qreal by = end.itself.y();

    //коэффициенты прямой
    qreal k = (ay-by)/(ax-bx);
    qreal b = ay - ax*k;
    return coefficients{k, b, false};
}
