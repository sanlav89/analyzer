#include "model.h"

#include "simplemethod.h"
#include "simulator.h"
#include "tfidentifier.h"

namespace model {

Model::Model()
//    : m_identifyMethod{new SimpleMethod}
    : m_identifyMethod{new TfIdentifier{"d:/Workspace/OTUS/analyzer/ml/saved_model", SpectrumSize}}
    , m_library{new NuclideLibrary{"nuclidelibrary.json"}}
    , m_isStarted{false}
{
    std::fill(m_spectrum.begin(), m_spectrum.end(), 1);
}

void Model::addObserver(ObserverPtr observer)
{
    m_observers.push_back(observer);
}

void Model::removeObserver(ObserverPtr observer)
{
    m_observers.remove(observer);
}

void Model::setEnPoly(const poly_t &enpoly)
{
    m_enpoly = enpoly;
    notifyUpdateEnergyScale();
}

void Model::receiveNewSpectrumData(const spectrum_t &spectrum)
{
    if (!m_isStarted) {
        return;
    }

    // Accumullate spectrum
    auto n = 0;
    auto genSample = [&n, spectrum, this] {
        sample_t result = 0;
        result = spectrum[n] + m_spectrum[n];
        n++;
        return result;
    };
    std::generate(m_spectrum.begin(), m_spectrum.end(), genSample);
    notifySpectrumChanged();

    // Identify nuclides
    auto probas = m_identifyMethod->identify(m_spectrum);
    m_nuclides = m_library->nuclides(probas);
    notifyNuclidesChanged();
}

void Model::clearSpectrum()
{
    std::fill(m_spectrum.begin(), m_spectrum.end(), 1);
    m_nuclides.clear();
    notifySpectrumChanged();
    notifyNuclidesChanged();
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

void Model::notifyUpdateEnergyScale()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateEnergyScale(m_enpoly);
    }
}

void Model::setIsStarted(bool isStarted)
{
    m_isStarted = isStarted;
}


}

