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
    for (auto i = 0u; i < m_spectrum.size(); i++) {
        m_spectrum[i] += spectrum[i];
    }
    // TODO: notify view
    auto probas = m_identifyMethod->identify(m_spectrum);
    auto nuclides = m_library->nuclides(probas);
    // TODO: notify view
    calcActivities(m_spectrum, nuclides);
    // TODO: notify view
}

void Model::clear()
{
    std::fill(m_spectrum.begin(), m_spectrum.end(), 0);
}

}

