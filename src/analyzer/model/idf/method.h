#pragma once

#include "utils/types.h"

namespace analyzer {
namespace model {
namespace idf {

class Method
{
public:
    virtual ~Method() = default;
    virtual utils::probas_t identify(const utils::spectrum_t &spectrum) = 0;
};

using MethodPtr = std::shared_ptr<Method>;

}
}
}

