#include <model/engine.h>
#include <view/mainwidget.h>
#include <ctrl/controller.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    detector::model::Engine model;
    detector::view::MainWidget view(model.energyPoly(), model.nuclidesNames(), model.measuredNames());
    detector::ctrl::Controller ctrl(&view, &model);

    return a.exec();
}
