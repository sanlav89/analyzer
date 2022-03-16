#pragma once

#include <list>
#include "model/nuclidelibrary.h"
#include "model/method.h"
#include "view/observer.h"

namespace model {

using namespace idf;
using namespace view;

class Analyzer
{
public:
    Analyzer();
    ~Analyzer() = default;

    void addObserver(Observer *observer);
    void removeObserver(Observer *observer);

    void setEnPoly(const poly_t &enpoly);
    void receiveNewSpectrumData(const spectrum_t &spectrum);
    void clearSpectrum();

    void setIsStarted(bool isStarted);

private:

    void notifySpectrumChanged();
    void notifyNuclidesChanged();
    void notifyUpdateEnergyScale();

    std::list<Observer *> m_observers;

    spectrum_t m_spectrum;
    nuclides_t m_nuclides;
    poly_t m_enpoly;

    MethodPtr m_identifyMethod;
    NuclideLibraryPtr m_library;
    bool m_isStarted;

};

}

