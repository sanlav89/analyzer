#pragma once

#include "identifymethod.h"
#include <iostream>

namespace idf {

class DeconvMethod : public IdentifyMethod
{
public:
    DeconvMethod() = default;

    virtual probas_t identify(const spectrum_t &)
    {
        std::cout << "Identified with Deconvolution Method" << std::endl;
        return {};
    }
};

}
