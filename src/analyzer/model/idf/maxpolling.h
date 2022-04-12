#pragma once

#include <model/idf/method.h>
#include <iostream>

namespace analyzer {
namespace model {
namespace idf {

class MaxPolling : public Method
{
public:
    MaxPolling() = default;

    utils::probas_t identify(const utils::spectrum_t &) override
    {
        std::cout << "NOT Identified with Simple Max Polling Method"
                     ", because this method need to be implement!" << std::endl;
        return {};
    }
};

}
}
}
