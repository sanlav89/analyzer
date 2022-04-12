#pragma once

#include <simulator/generator.h>

namespace sim {
namespace gen {

class Modeling : public Generator
{
public:
    Modeling(
            const utils::nuclides_t &nuclidesAll,
            const utils::poly_t &energyPoly,
            const utils::poly_t &fwhmPoly,
            const utils::poly_t &efficiencyPoly,
            const double &tlive
            );

    void updateActivity(size_t id, utils::activity_t activity) override;
    void updateName(const utils::name_t &) override;
    utils::spectrum_t spectrum() const override;
    utils::names_t names() const override;

private:

    void recalcSpectrum();

    utils::nuclides_t m_nuclidesAll;
    utils::poly_t m_energyPoly;
    utils::poly_t m_fwhmPoly;
    utils::poly_t m_efficiencyPoly;
    double m_tlive;

    std::vector<utils::energy_t> m_energies;
    std::vector<utils::activity_t> m_activities;
    utils::spectrum_t m_spectrum;

    const double m_a = 5;
    const double m_b = -0.003;
    const double m_c = 0.5;
    const double m_d = -0.002;

};

using ModelingPtr = std::shared_ptr<Modeling>;

}
}

