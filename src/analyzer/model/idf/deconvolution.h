#pragma once

#include <model/idf/method.h>
#include <iostream>

namespace analyzer {
namespace model {
namespace idf {

class Deconvolution : public Method
{
public:
    Deconvolution() = default;

    virtual probas_t identify(const spectrum_t &)
    {
        std::cout << "NOT Identified with Deconvolution Method"
                     ", because this method need to be implement!" << std::endl;
        return {};
    }
};

}
}
}
