#pragma once

#include "utils/types.h"

namespace idf {

using namespace utils;

class IdentifyMethod
{
public:
    virtual ~IdentifyMethod() = default;
    virtual probas_t identify(const spectrum_t &spectrum) = 0;
};

using IdentifyMethodPtr = std::unique_ptr<IdentifyMethod>;

}

