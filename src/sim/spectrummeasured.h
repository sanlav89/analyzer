#pragma once

#include <sim/spectrumgen.h>
#include <map>

namespace sim {

class SpectrumMeasured : public SpectrumGen
{
public:
    SpectrumMeasured();

    void updateActivity(size_t, utils::activity_t) override;
    void updateName(const std::string &name) override;
    utils::spectrum_t spectrum() const override;
    utils::poly_t energyPoly() const override;

    void loadFromDirectory(const utils::path_t &path);
    void changeCurrentName(const std::string &name);
    utils::spectrum_t spectrum() const override;
    std::vector<std::string> names() const;

private:
    std::map<std::string, utils::spectrum_t> m_spectrumMap;
    utils::spectrum_t m_currentSpectrum;

};

}

