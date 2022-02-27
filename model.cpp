#include "model.h"

#include "simplemethod.h"

namespace model {

activities_t calcActivities(const spectrum_t &, const nuclides_t &)
{
    return 10;
}

Model::Model()
    : m_identifyMethod{new SimpleMethod}
    , m_library{new NuclideLibrary}
{
}

void Model::accum(const spectrum_t &spectrum)
{
    m_spectrum += spectrum;
    // TODO: notify view
    auto probas = m_identifyMethod->identify(m_spectrum);
    auto nuclides = m_library->nuclides(probas);
    // TODO: notify view
    calcActivities(m_spectrum, nuclides);
    // TODO: notify view
}

void Model::clear()
{
    m_spectrum = 0;
}

}

