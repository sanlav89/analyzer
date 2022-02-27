#pragma once

#include "types.h"
#include <iostream>

namespace view {

class IView
{
public:
    virtual void updateSpectrum(const data_t &data) = 0;
    virtual void updateNuclides(const nuclides_t &nuclides) = 0;
    virtual void updateActivities(const activities_t &activities) = 0;
    virtual void updateState() = 0;
};

class View : public IView
{
public:
    View() = default;

    virtual ~View() = default;

    virtual void updateSpectrum(const data_t &)
    {
        std::cout << "Spectrum was updated" << std::endl;
    }

    virtual void updateNuclides(const nuclides_t &)
    {
        std::cout << "Nuclides was updated" << std::endl;
    }

    virtual void updateActivities(const activities_t &)
    {
        std::cout << "Activities was updated" << std::endl;
    }

    virtual void updateState()
    {
        std::cout << "State was updated" << std::endl;
    }
};

using ViewPtr = std::unique_ptr<View>;

}

