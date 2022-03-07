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
    , m_library{new NuclideLibrary}
{
}

void Model::addObserver(ObserverPtr observer)
{
    m_observers.push_back(observer);
}

void Model::removeObserver(ObserverPtr observer)
{
    m_observers.remove(observer);
}

void Model::setEnPoly(const enpoly_t &enpoly)
{
    m_enpoly = enpoly;
    notifyUpdateEnergyScale();
}

void Model::receiveNewSpectrumData(const spectrum_t &spectrum)
{
    // Accumullate spectrum
    m_spectrum = spectrum;
    notifySpectrumChanged();

    // Identify nuclides
    m_nuclides = m_library->nuclides({});
    notifyNuclidesChanged();

    // Calculate Activities
    m_activities = calcActivities(m_spectrum, m_nuclides);
    notifyActivitiesChanged();
}

void Model::clearSpectrum()
{
    std::fill(m_spectrum.begin(), m_spectrum.end(), 0);
    m_nuclides.clear();
    m_activities.clear();
    notifySpectrumChanged();
    notifyNuclidesChanged();
    notifyActivitiesChanged();
}

void Model::notifySpectrumChanged()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateSpectrum(m_spectrum);
    }
}

void Model::notifyNuclidesChanged()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateNuclides(m_nuclides);
    }
}

void Model::notifyActivitiesChanged()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateActivities(m_activities);
    }
}

void Model::notifyUpdateEnergyScale()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateEnergyScale(m_enpoly);
    }
}


}

