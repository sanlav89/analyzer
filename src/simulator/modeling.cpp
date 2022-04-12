#include "modeling.h"
#include <utils/matlab/matlab.h>
#include <cassert>
#include <cmath>

namespace sim {
namespace gen {

Modeling::Modeling(
        const utils::nuclides_t &nuclidesAll,
        const utils::poly_t &energyPoly,
        const utils::poly_t &fwhmPoly,
        const utils::poly_t &efficiencyPoly,
        const double &tlive
        )
    : m_nuclidesAll{nuclidesAll}
    , m_energyPoly{energyPoly}
    , m_fwhmPoly{fwhmPoly}
    , m_efficiencyPoly{efficiencyPoly}
    , m_tlive{tlive}
{
    m_energies = utils::matlab::calcEnergy(m_energyPoly);
    assert(m_nuclidesAll.size() > 0);
    m_activities.resize(m_nuclidesAll.size());
    std::fill(m_activities.begin(), m_activities.end(), 0);
    std::fill(m_spectrum.begin(), m_spectrum.end(), 0);
}

void Modeling::updateActivity(size_t id, utils::activity_t activity)
{
    assert(id < m_activities.size());
    m_activities[id] = activity;
    recalcSpectrum();
}

void Modeling::updateName(const utils::name_t &)
{
    assert(false);
}

utils::spectrum_t Modeling::spectrum() const
{
    return m_spectrum;
}

utils::names_t Modeling::names() const
{
    assert(false);
    return {};
}

void Modeling::recalcSpectrum()
{
    std::array<double, utils::SpectrumSize> spectrumReal;
    std::fill(spectrumReal.begin(), spectrumReal.end(), 0);

    // activities
    for (auto idxn = 0u; idxn < m_nuclidesAll.size(); idxn++) {
        // gaussians
        double tlive = m_activities[idxn] * m_tlive;
        for (const auto &line : m_nuclidesAll[idxn].lines) {
            double eff = utils::matlab::calcEffifiency(line.energy, m_efficiencyPoly);
            double area = eff * line.intensity * m_activities[idxn] * tlive * 500;
            auto sigma = utils::matlab::calcFwhm(line.energy, m_fwhmPoly) / (2*sqrt(2*log(2)));
            utils::matlab::vector_t shape = utils::matlab::gaussian(m_energies, line.energy, sigma, area);
            for (auto idxs = 0; idxs < utils::SpectrumSize; idxs++) {
                spectrumReal[idxs] += shape[idxs];
            }
        }
        // substrate
        auto substrate = utils::matlab::substrateModel(m_energies, m_a * tlive, m_b, m_c * tlive, m_d);
        for (auto idxs = 0; idxs < utils::SpectrumSize; idxs++) {
            spectrumReal[idxs] += substrate[idxs];
        }
    }

    for (auto idxs = 0; idxs < utils::SpectrumSize; idxs++) {
        m_spectrum[idxs] = round(spectrumReal[idxs]);
    }
}

}

}
