#include "detectorwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DetectorWidget w;
    w.show();
    return a.exec();
}
