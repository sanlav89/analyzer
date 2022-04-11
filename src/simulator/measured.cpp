#include "measured.h"
#include <cassert>
#include <utils/utils.h>

namespace sim {
namespace gen {

Measured::Measured(const std::map<utils::name_t, utils::spectrum_t> &spectrumMap)
    : m_spectrumMap(spectrumMap)
{
    std::fill(m_currentSpectrum.begin(), m_currentSpectrum.end(), 0);
}

void Measured::updateActivity(size_t, utils::activity_t)
{
    assert(false);
}

void Measured::updateName(const utils::name_t &name)
{
    assert(m_spectrumMap.find(name) != m_spectrumMap.end());
    m_currentSpectrum = m_spectrumMap.at(name);
}

utils::spectrum_t Measured::spectrum() const
{
    return m_currentSpectrum;
}

utils::names_t Measured::names() const
{
    utils::names_t result;
    result.reserve(m_spectrumMap.size());
    for (const auto &pair : m_spectrumMap) {
        result.push_back(pair.first);
    }
    return result;
}

}

}
