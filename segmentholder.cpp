#include "segmentholder.h"
#include "randgen.h"
#include "square.h"

void SegmentHolder::clipSegments()
{
    if (!(*rectActive)) {
        return;
    }
    square sq(rect->first, rect->second, [this](const QPair<QPoint, QPoint> &segment) {
        clippedSegments.append(segment);
    });
    for (const auto &seg : originalSegments) {
        sq.handleSegment(seg);
    }
}

void SegmentHolder::setNewSegments(int amount, int xmax, int ymax)
{
    RandomGenerator xgen(0, xmax);
    RandomGenerator ygen(0, ymax);
    originalSegments.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        originalSegments.append(qMakePair(QPoint(xgen(), ygen()), QPoint(xgen(), ygen())));
    }
    if (*rectActive) {
        clipSegments();
    }
}

SegmentHolder::SegmentHolder(QObject *parent)
    : QObject(parent)
{}

const QVector<QPair<QPoint, QPoint> > &SegmentHolder::getOrig() const {return originalSegments;}

const QVector<QPair<QPoint, QPoint> > &SegmentHolder::getClipped() const {return clippedSegments;}

void SegmentHolder::assertRectData(const QPair<QPoint, QPoint> *r, const bool *isactive)
{
    rect = r;
    rectActive = isactive;
}

void SegmentHolder::eraseRectangle()
{
    clippedSegments.clear();
    emit update();
}

void SegmentHolder::receivedRectangle()
{
    clippedSegments.clear();
    clipSegments();
    emit update();
}

void SegmentHolder::makeSegments(int amount, int xmax, int ymax)
{
    originalSegments.clear();
    clippedSegments.clear();
    setNewSegments(amount, xmax, ymax);
    emit update();
}
