#pragma once

#include "types.h"
#include <iostream>

namespace view {

class IView
{
public:
    virtual void updateSpectrum(const spectrum_t &spectrum) = 0;
    virtual void updateNuclides(const nuclides_t &nuclides) = 0;
    virtual void updateActivities(const activities_t &activities) = 0;
    virtual void updateEnergyScale(const enpoly_t &enpoly) = 0;
};

}

