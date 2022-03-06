#pragma once

#include "types.h"
#include <iostream>

namespace dao {

class Detector
{
public:
    virtual ~Detector() = default;
    virtual void connect() = 0;
    virtual data_t read() = 0;
    virtual void disconnect() = 0;
};

using DetectorPtr = std::unique_ptr<Detector>;

}

