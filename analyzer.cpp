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

    DetectorPtr d{new Simulator({"Cs137_15_OSGI.spe", "Th228_15_OSGI.spe"})};
    view::MainWidget g;
    model::ModelPtr m{new model::Model};
    m->addObserver(&g);

    ctrl::Controller controller(std::move(m), &g);
    controller.setDetector(std::move(d));
    controller.execute();

    return a.exec();
}
