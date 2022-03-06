#include <iostream>

#include "simulator.h"
#include "iview.h"
#include "model.h"

#include <QApplication>
#include "view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << "Hello form Analyzer" << std::endl;

    view::View g;
    g.show();

    model::Model model;
    g.updateSpectrum(model.spectrum());
    g.updateNuclides(model.nuclides());
    g.updateActivities(model.activities());

    return a.exec();
}
