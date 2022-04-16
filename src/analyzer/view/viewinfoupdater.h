#pragma once

#include <utils/types.h>

namespace analyzer {
namespace view {

class ViewInfoUpdater
{
public:
    virtual ~ViewInfoUpdater() = default;
    virtual void updateSpectrum(const utils::spectrum_t &spectrum) = 0;
    virtual void updateNuclides(const utils::nuclides_t &nuclides) = 0;
    virtual void updateEnergyScale(const utils::poly_t &enpoly) = 0;
    virtual void updateStatusMsg(const std::string &msg) = 0;
};

}
}

