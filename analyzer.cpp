#include <iostream>

#include "idao.h"
#include "iview.h"

int main()
{
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

    return 0;
}
