#include <iostream>

//#include "simulator.h"
#include "tcpaccess.h"
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
    model::ModelPtr m{new model::Model};
    m->addObserver(&g);

    ctrl::Controller controller(std::move(m), &g);
//    auto countRate = 100;
//    DetectorAccessPtr d{new Simulator({"Th228_15_OSGI.spe"}, countRate, &controller)};
//    DetectorAccessPtr d{new Simulator({"Eu152_15_OSGI.spe"}, countRate, &controller)};
//    DetectorAccessPtr d{new Simulator({"Am241_15_OSGI.spe"}, countRate, &controller)};
//    DetectorAccessPtr d{new Simulator({"Co60_15_OSGI.spe"}, countRate, &controller)};
//    DetectorAccessPtr d{new Simulator({"Ba133_15_OSGI.spe"}, countRate, &controller)};
//    DetectorAccessPtr d{new Simulator({"Cs137_15_OSGI.spe"}, countRate, &controller)};
//    DetectorAccessPtr d{new Simulator({"Cs137_15_OSGI.spe", "Th228_15_OSGI.spe"}, 1000, &controller)};
    DetectorAccessPtr d{new TcpAccess(9999, &controller)};
    controller.setDetector(std::move(d));

    return a.exec();
}
