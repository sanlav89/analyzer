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

    dao::Simulator detector({"Cs137_15_OSGI.spe", "Th228_15_OSGI.spe"});

    detector.connect();
    auto data = detector.read();
    detector.disconnect();

    for (int i = 1000; i < 1024; i++) {
        std::cout << data.second[i] << " " << data.second.data()[i] << std::endl;
    }

    view::View g;
    g.show();

    return a.exec();
}
