#pragma once

#include "types.h"

namespace view {

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void updateSpectrum(const spectrum_t &spectrum) = 0;
    virtual void updateNuclides(const nuclides_t &nuclides) = 0;
    virtual void updateEnergyScale(const enpoly_t &enpoly) = 0;
    virtual void updateStatusMsg(const std::string &msg) = 0;
};

}

