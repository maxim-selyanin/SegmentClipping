#include "application.h"

void application::toMakeSegments(int amount)
{
    sh->makeSegments(amount, dw->size().width(), dw->size().height());
}

application::application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    sh = new SegmentHolder(this);
    dw = new DrawWindow(sh->getOrig(), sh->getClipped());
    sh->assertRectData(dw->getRect(), dw->getActivity());

    //вызывается создание новых сегментов
    connect(dw, &DrawWindow::makeSegments, this, &application::toMakeSegments);

    //удаляется существующее окно
    connect(dw, &DrawWindow::eraseRectangleSgn, sh, &SegmentHolder::eraseRectangle);

    //рисовальный виджет кидает сигнал о новом окне
    connect(dw, &DrawWindow::gotNewRect, sh, &SegmentHolder::receivedRectangle);

    //окно обновляется, когда это говорит делать обрезатель отрезков
    connect(sh, &SegmentHolder::update, dw, &DrawWindow::upd);

    dw->show();
}
