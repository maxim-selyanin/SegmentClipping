#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QPair>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class DrawWindow : public QWidget
{
    Q_OBJECT

    QLabel *amountOfSegmentsLabel = nullptr;
    QLineEdit *amountOfSegments = nullptr;
    QPushButton *generateSegments = nullptr;
    QPushButton *eraseRectangleBtn = nullptr;

    const QVector<QPair<QPoint, QPoint>> &originalSegments;
    const QVector<QPair<QPoint, QPoint>> &clippedSegments;
    QPair<QPoint, QPoint> rect;
    bool rectActive = false;
    bool makingRect = false;

    QColor origSegColor = Qt::blue;
    QColor clippedSegColor = Qt::red;
    QColor rectColor = Qt::darkGreen;
    QColor rectAngleColor = Qt::darkGreen;

    void drawOrigSeg(QPainter &p);
    void drawClippedSeg(QPainter &p);
    void drawRect(QPainter &p);

public:
    explicit DrawWindow(const QVector<QPair<QPoint, QPoint>> &origSg,
                        const QVector<QPair<QPoint, QPoint>> &clpSg,
                        QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    const QPair<QPoint, QPoint> *getRect()const;
    const bool *getActivity()const;



public slots:
    void upd();

private slots:
    void eraseRectangle();
    void toMakeSegs();

signals:
    void gotNewRect();
    void makeSegments(int amount);
    void eraseRectangleSgn();
};

#endif // DRAWWINDOW_H
