#pragma once

#include <simulator/generator.h>
#include <map>

namespace sim {
namespace gen {

class Measured;
using MeasuredPtr = std::shared_ptr<Measured>;

class Measured : public Generator
{
public:
    Measured(const std::map<utils::name_t, utils::spectrum_t> &spectrumMap);

    void updateActivity(size_t, utils::activity_t) override;
    void updateName(const utils::name_t &name) override;
    utils::spectrum_t spectrum() const override;
    utils::names_t names() const override;

private:
    std::map<utils::name_t, utils::spectrum_t> m_spectrumMap;
    utils::spectrum_t m_currentSpectrum;

};

}

}

