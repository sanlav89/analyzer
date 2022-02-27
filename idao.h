#pragma once

#include "types.h"
#include <iostream>

namespace dao {

class IDao
{
public:
    virtual void connect() = 0;
    virtual data_t read() = 0;
    virtual void disconnect() = 0;
};

class Dao : public IDao
{
public:
    Dao() = default;

    virtual ~Dao() = default;

    virtual void connect()
    {
        std::cout << "Connected" << std::endl;
    }

    virtual data_t read()
    {
        std::cout << "Read" << std::endl;
        return 0;
    }

    virtual void disconnect()
    {
        std::cout << "Disconnected" << std::endl;
    }
};

using DaoPtr = std::unique_ptr<Dao>;

}

