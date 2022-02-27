#pragma once

#include "identifymethod.h"
#include <iostream>

namespace idf {

class SimpleMethod : public IdentifyMethod
{
public:
    SimpleMethod() = default;

    virtual probas_t identify(const spectrum_t &)
    {
        std::cout << "Identified with Simple Max Polling Method" << std::endl;
        return {};
    }
};

}
