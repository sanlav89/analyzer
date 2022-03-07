#include <iostream>

#include "simulator.h"
#include "view.h"
#include "model.h"

#include <QApplication>
#include "mainwidget.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << "Hello form Analyzer" << std::endl;

    view::MainWidget g;
//    g.show();

    ctrl::Controller controller(&g);

//    model::Model model;
//    g.updateEnergyScale(model.enpoly());
//    g.updateSpectrum(model.spectrum());
//    g.updateNuclides(model.nuclides());
//    g.updateActivities(model.activities());

    return a.exec();
}
