#pragma once

#include "nuclidelibrary.h"
#include "spectrumgen.h"

namespace sim {

using namespace model;

class SpectrumModeling
{
public:
    SpectrumModeling();

    void update(size_t id, activity_t activity);
    spectrum_t spectrum() const;
    std::vector<std::string> nuclideNames() const;
    poly_t energyPoly() const;

private:

    void recalcSpectrum();

    NuclideLibraryPtr m_library;
    std::vector<energy_t> m_energies;
    std::vector<activity_t> m_activities;
    nuclides_t m_nuclidesAll;
    spectrum_t m_spectrum;

    const poly_t m_energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
    const poly_t m_fwhmPoly{0.3180643473,1.2086508047,0.0274012077};
    const poly_t m_efficiencyPoly{-19.424696, 20.563331, -7.695772, 0.906304};
    const double m_tlive = 3600;
    const double m_a = 5;
    const double m_b = -0.003;
    const double m_c = 0.5;
    const double m_d = -0.002;

};

}



