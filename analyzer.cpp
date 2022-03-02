#include <iostream>

#include "idao.h"
#include "iview.h"
#include "model.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << "Hello form Analyzer" << std::endl;

    dao::DaoPtr dao{new dao::Dao};
    dao->connect();
    dao->read();
    dao->disconnect();

    view::ViewPtr view{new view::View};
    view->updateSpectrum(0);
    view->updateNuclides(0);
    view->updateActivities(0);
    view->updateState();

    model::ModelPtr model{new model::Model};
    model->accum(0);

    QWidget w;
    w.show();
    return a.exec();
}
