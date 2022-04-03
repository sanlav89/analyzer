#pragma once

#include <sim/generator.h>
#include <nuclidelibrary.h>

namespace sim {

namespace spectrum {

class Modeling : public Generator
{
public:
    Modeling();

    void updateActivity(size_t id, utils::activity_t activity) override;
    void updateName(const utils::name_t &) override;
    utils::spectrum_t spectrum() const override;
    utils::poly_t energyPoly() const override;
    utils::names_t names() const override;

private:

    void recalcSpectrum();

    model::NuclideLibraryPtr m_library;
    std::vector<utils::energy_t> m_energies;
    std::vector<utils::activity_t> m_activities;
    utils::nuclides_t m_nuclidesAll;
    utils::spectrum_t m_spectrum;

    const utils::poly_t m_energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
    const utils::poly_t m_fwhmPoly{0.3180643473,1.2086508047,0.0274012077};
    const utils::poly_t m_efficiencyPoly{-19.424696, 20.563331, -7.695772, 0.906304};
    const double m_tlive = 3600;
    const double m_a = 5;
    const double m_b = -0.003;
    const double m_c = 0.5;
    const double m_d = -0.002;

};

}

}

