#pragma once

#include "identifymethod.h"
#include <iostream>

namespace idf {

class MLIdentifier : public IdentifyMethod
{
public:
    MLIdentifier() = default;

    virtual ~MLIdentifier() = default;

    virtual probas_t identify(const spectrum_t &)
    {
        std::cout << "Identified with ML Method (TensorFlow)" << std::endl;
        return {};
    }
};

}

