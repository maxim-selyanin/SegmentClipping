#include "drawwindow.h"
#include <QPainter>
#include <QMouseEvent>

void DrawWindow::drawOrigSeg(QPainter &p)
{
    if (originalSegments.empty()) {
        return;
    }
    p.setPen(origSegColor);
    for (const auto &s: originalSegments) {
        p.drawLine(s.first, s.second);
    }
}

void DrawWindow::drawClippedSeg(QPainter &p)
{
    if (clippedSegments.empty()) {
        return;
    }
    QPen pen;
    pen.setWidth(3);
    pen.setColor(clippedSegColor);
    p.setPen(pen);
    for (const auto &s: clippedSegments) {
        p.drawLine(s.first, s.second);
    }
}

void DrawWindow::drawRect(QPainter &p)
{
    if (rectActive) {
        p.setPen(rectColor);
        QPoint topleft(qMin(rect.first.x(), rect.second.x()), qMax(rect.first.y(), rect.second.y()));
        QPoint bottomright(qMax(rect.first.x(), rect.second.x()), qMin(rect.first.y(), rect.second.y()));
        QRect r(topleft, bottomright);
        p.drawRect(r);

        p.setPen(rectAngleColor);
        p.drawPoint(rect.first);
        p.drawPoint(rect.second);
    }
}

DrawWindow::DrawWindow(const QVector<QPair<QPoint, QPoint> > &origSg,
                       const QVector<QPair<QPoint, QPoint> > &clpSg,
                       QWidget *parent)
    : QWidget(parent)
    , originalSegments(origSg)
    , clippedSegments(clpSg)
{
    setGeometry(500,100,1000, 700);
    amountOfSegmentsLabel = new QLabel("how many segments", this);
    amountOfSegmentsLabel->setGeometry(10, 10, 150, 30);
    amountOfSegments = new QLineEdit(this);
    amountOfSegments->setGeometry(160, 10, 50, 30);
    generateSegments = new QPushButton("make segments", this);
    generateSegments->setGeometry(250, 10, 140, 30);
    eraseRectangleBtn = new QPushButton("delete rectangle", this);
    eraseRectangleBtn->setGeometry(400, 10, 140, 30);

    connect(generateSegments, &QPushButton::pressed, this, &DrawWindow::toMakeSegs);
    connect(eraseRectangleBtn, &QPushButton::pressed, this, &DrawWindow::eraseRectangleSgn);
    connect(eraseRectangleBtn, &QPushButton::pressed, this, &DrawWindow::eraseRectangle);
}

void DrawWindow::mousePressEvent(QMouseEvent *event)
{
    if (
            //!rectActive &&
            event && event->button() == Qt::LeftButton) {
        rect.first = event->pos();
        rect.second = rect.first;
        makingRect = true;
        rectActive = true;
        this->update();
    }
}

void DrawWindow::mouseReleaseEvent(QMouseEvent *)
{
    makingRect = false;
    emit gotNewRect();
}

void DrawWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (makingRect && event) {
        rect.second = event->pos();
        this->update();
    }
}

void DrawWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawOrigSeg(painter);
    drawClippedSeg(painter);
    drawRect(painter);
}

const QPair<QPoint, QPoint> *DrawWindow::getRect() const {return &rect;}

const bool *DrawWindow::getActivity() const {return &rectActive;}

void DrawWindow::eraseRectangle()
{
    rectActive = false;
    makingRect = false;
}

void DrawWindow::toMakeSegs()
{
    int amount = amountOfSegments->text().toInt();
    if (amount > 0) {
        emit makeSegments(amount);
    }
}

void DrawWindow::upd()
{
    this->update();
}
