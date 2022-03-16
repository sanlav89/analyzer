#pragma once

#include "utils/types.h"
#include <map>

namespace sim {

using namespace utils;
using path_t = std::string;

class SpectrumMeasured
{
public:
    SpectrumMeasured();
    void loadFromDirectory(const path_t &path);
    void changeCurrentName(const std::string &name);
    spectrum_t spectrum() const;
    std::vector<std::string> names() const;

private:
    std::map<std::string, spectrum_t> m_spectrumMap;
    spectrum_t m_currentSpectrum;

};

}

