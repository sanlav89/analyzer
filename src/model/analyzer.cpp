#include "analyzer.h"
#include "convneuralnet.h"
#include <algorithm>

namespace model {

Analyzer::Analyzer()
    : m_identifyMethod{new ConvNeuralNet{"./data/saved_model", SpectrumSize}}
    , m_library{NuclideLibrary::instance("./data/nuclidelibrary.json")}
    , m_isStarted{false}
{
    std::fill(m_spectrum.begin(), m_spectrum.end(), 1);
}

void Analyzer::addObserver(Observer *observer)
{
    m_observers.push_back(observer);
}

void Analyzer::removeObserver(Observer *observer)
{
    m_observers.remove(observer);
}

void Analyzer::setEnPoly(const poly_t &enpoly)
{
    m_enpoly = enpoly;
    notifyUpdateEnergyScale();
}

void Analyzer::receiveNewSpectrumData(const spectrum_t &spectrum)
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

void Analyzer::clearSpectrum()
{
    std::fill(m_spectrum.begin(), m_spectrum.end(), 1);
    m_nuclides.clear();
    notifySpectrumChanged();
    notifyNuclidesChanged();
}

void Analyzer::notifySpectrumChanged()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateSpectrum(m_spectrum);
    }
}

void Analyzer::notifyNuclidesChanged()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateNuclides(m_nuclides);
    }
}

void Analyzer::notifyUpdateEnergyScale()
{
    if (m_observers.empty()) {
        return;
    }
    for (auto observer : m_observers) {
        observer->updateEnergyScale(m_enpoly);
    }
}

void Analyzer::setIsStarted(bool isStarted)
{
    m_isStarted = isStarted;
}


}

