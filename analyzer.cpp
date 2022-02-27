#include <iostream>

#include "idao.h"

int main()
{
    std::cout << "Hello form Analyzer" << std::endl;

    dao::DaoPtr dao{new dao::Dao};
    dao->connect();
    dao->read();
    dao->disconnect();

    return 0;
}
