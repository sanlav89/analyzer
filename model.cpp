#include "model.h"

#include "simplemethod.h"
#include "simulator.h"

namespace model {

activities_t calcActivities(const spectrum_t &, const nuclides_t &)
{
    activities_t result{
        {"Eu-152", 0.625}
    };
    return result;
}

Model::Model()
    : m_identifyMethod{new SimpleMethod}
    , m_detector{new Simulator({"Cs137_15_OSGI.spe", "Th228_15_OSGI.spe"})}
    , m_library{new NuclideLibrary}
{
    m_detector->connect();
}

spectrum_t Model::spectrum() const
{
    return m_detector->read().second;
}

nuclides_t Model::nuclides() const
{
    return m_library->nuclides(m_identifyMethod->identify(m_spectrum));
}

activities_t Model::activities() const
{
    return calcActivities(m_spectrum, {});
}

}

