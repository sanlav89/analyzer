#pragma once

#include "utils/types.h"

namespace view {

using namespace utils;

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void updateSpectrum(const spectrum_t &spectrum) = 0;
    virtual void updateNuclides(const nuclides_t &nuclides) = 0;
    virtual void updateEnergyScale(const poly_t &enpoly) = 0;
    virtual void updateStatusMsg(const std::string &msg) = 0;
};

}

