#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include <QObject>
#include "segmentholder.h"
//#include "controlinterface.h"
#include "drawwindow.h"

class application : public QApplication
{
    Q_OBJECT

    SegmentHolder *sh = nullptr;
    //ControlInterface *ci = nullptr;
    DrawWindow *dw = nullptr;

private slots:
    void toMakeSegments(int amount);

public:
    application(int &argc, char **argv);
    ~application() = default;
};

#endif // APPLICATION_H
