#ifndef SEGMENTHOLDER_H
#define SEGMENTHOLDER_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QPair>

class SegmentHolder : public QObject
{
    Q_OBJECT

    QVector<QPair<QPoint, QPoint>> originalSegments{};
    QVector<QPair<QPoint, QPoint>> clippedSegments{};
    const QPair<QPoint, QPoint> *rect = nullptr;
    const bool *rectActive = nullptr;

    void clipSegments();
    void setNewSegments(int amount, int xmax, int ymax);

public:
    explicit SegmentHolder(QObject *parent = nullptr);

    const QVector<QPair<QPoint, QPoint>> &getOrig()const;
    const QVector<QPair<QPoint, QPoint>> &getClipped()const;

    void assertRectData(const QPair<QPoint, QPoint> *r, const bool *isactive);

public slots:
    void eraseRectangle();//удаляет текущее окно
    void receivedRectangle();//делает новое окно
    void makeSegments(int amount, int xmax, int ymax);//делает новые отрезки

signals:
    void update();
};

#endif // SEGMENTHOLDER_H
