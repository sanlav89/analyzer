#pragma once

#include <sim/generator.h>
#include <map>

namespace sim {

namespace spectrum {

class Measured : public Generator
{
public:
    Measured(const utils::path_t &path);

    void updateActivity(size_t, utils::activity_t) override;
    void updateName(const utils::name_t &name) override;
    utils::spectrum_t spectrum() const override;
    utils::poly_t energyPoly() const override;
    utils::names_t names() const override;

private:
    std::map<utils::name_t, utils::spectrum_t> m_spectrumMap;
    utils::spectrum_t m_currentSpectrum;

    void loadFromDirectory(const utils::path_t &path);

};

}

}

