#pragma once

#include "utils/types.h"

namespace analyzer {
namespace model {
namespace idf {

using namespace utils;

class Method
{
public:
    virtual ~Method() = default;
    virtual probas_t identify(const spectrum_t &spectrum) = 0;
};

using MethodPtr = std::shared_ptr<Method>;

}
}
}

