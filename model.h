#pragma once

#include <list>
#include "nuclidelibrary.h"
#include "identifymethod.h"
#include "observer.h"

using namespace idf;
using namespace view;

namespace model {

activities_t calcActivities(const spectrum_t &spectrum, const nuclides_t &nuclides);

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

private:

    void notifySpectrumChanged();
    void notifyNuclidesChanged();
    void notifyActivitiesChanged();
    void notifyUpdateEnergyScale();

    std::list<ObserverPtr> m_observers;

    spectrum_t m_spectrum;
    nuclides_t m_nuclides;
    activities_t m_activities;
    enpoly_t m_enpoly;

    IdentifyMethodPtr m_identifyMethod;
    NuclideLibraryPtr m_library;


};

using ModelPtr = std::unique_ptr<Model>;

}

