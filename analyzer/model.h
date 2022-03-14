#pragma once

#include <list>
#include "nuclidelibrary.h"
#include "identifymethod.h"
#include "observer.h"

using namespace idf;
using namespace view;

namespace model {

using ObserverPtr = Observer*;

class Model
{
public:
    Model();
    ~Model() = default;

    void addObserver(ObserverPtr observer);
    void removeObserver(ObserverPtr observer);

    void setEnPoly(const enpoly_t &enpoly);
    void receiveNewSpectrumData(const spectrum_t &spectrum);
    void clearSpectrum();

    void setIsStarted(bool isStarted);

private:

    void notifySpectrumChanged();
    void notifyNuclidesChanged();
    void notifyUpdateEnergyScale();

    std::list<ObserverPtr> m_observers;

    spectrum_t m_spectrum;
    nuclides_t m_nuclides;
    enpoly_t m_enpoly;

    IdentifyMethodPtr m_identifyMethod;
    NuclideLibraryPtr m_library;
    bool m_isStarted;

};

using ModelPtr = std::unique_ptr<Model>;

}

