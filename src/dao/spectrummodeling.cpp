#include "spectrummodeling.h"
#include "mathutils.h"
#include <cmath>
#include <cassert>

namespace sim {

using namespace mathutils;

SpectrumModeling::SpectrumModeling()
    : m_library(NuclideLibrary::instance("nuclidelibrary.json"))
{
    m_energies = calcEnergy(m_energyPoly);
    m_nuclidesAll = m_library->nuclidesAll();
    assert(m_nuclidesAll.size() > 0);
    m_activities.resize(m_library->numClasses());
    std::fill(m_activities.begin(), m_activities.end(), 0);
    std::fill(m_spectrum.begin(), m_spectrum.end(), 0);
}

void SpectrumModeling::update(size_t id, activity_t activity)
{
    assert(id < m_activities.size());
    m_activities[id] = activity;
    recalcSpectrum();
}

spectrum_t SpectrumModeling::spectrum() const
{
    return m_spectrum;
}

std::vector<std::string> SpectrumModeling::nuclideNames() const
{
    return m_library->nuclideNames();
}

poly_t SpectrumModeling::energyPoly() const
{
    return m_energyPoly;
}

void SpectrumModeling::recalcSpectrum()
{
    std::array<double, SpectrumSize> spectrumReal;
    std::fill(spectrumReal.begin(), spectrumReal.end(), 0);

    // activities
    for (auto idxn = 0u; idxn < m_library->numClasses(); idxn++) {
        // gaussians
        double tlive = m_activities[idxn] * m_tlive;
        for (const auto &line : m_nuclidesAll[idxn].lines) {
            double eff = calcEffifiency(line.energy, m_efficiencyPoly);
            double area = eff * line.intensity * m_activities[idxn] * tlive * 500;
            auto sigma = calcFwhm(line.energy, m_fwhmPoly) / (2*sqrt(2*log(2)));
            vector_t shape = gaussian(m_energies, line.energy, sigma, area);
            for (auto idxs = 0; idxs < SpectrumSize; idxs++) {
                spectrumReal[idxs] += shape[idxs];
            }
        }
        // substrate
        auto substrate = substrateModel(m_energies, m_a * tlive, m_b, m_c * tlive, m_d);
        for (auto idxs = 0; idxs < SpectrumSize; idxs++) {
            spectrumReal[idxs] += substrate[idxs];
        }
    }

    for (auto idxs = 0; idxs < SpectrumSize; idxs++) {
        m_spectrum[idxs] = round(spectrumReal[idxs]);
    }
}

}
