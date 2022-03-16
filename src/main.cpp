#include <iostream>
#include <QApplication>

#include "dao/tcpaccess.h"
#include "model/analyzer.h"
#include "view/mainwidget.h"
#include "ctrl/controller.h"
#include "sim/simulatorwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Analyzer
    view::MainWidget gui;
    model::Analyzer analyzer;
    analyzer.addObserver(&gui);
    ctrl::Controller controller(&analyzer, &gui);

    // Detector simulator
    SimulatorWidget w;
    w.show();

    return a.exec();
}
