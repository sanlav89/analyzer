#pragma once

#include <list>
#include <utils/nuclidelibrary/nuclidelibrary.h>
#include <model/idf/method.h>
#include <view/viewinfoupdater.h>

namespace analyzer {
namespace model {

class Analyzer
{
public:
    Analyzer();
    ~Analyzer() = default;

    void addObserver(view::ViewInfoUpdater *observer);
    void removeObserver(view::ViewInfoUpdater *observer);

    void setEnPoly(const utils::poly_t &enpoly);
    void receiveNewSpectrumData(const utils::spectrum_t &spectrum);
    void clearSpectrum();

    void setIsStarted(bool isStarted);

    void setIdentifyMethod(const idf::MethodPtr &identifyMethod);

private:

    void notifySpectrumChanged();
    void notifyNuclidesChanged();
    void notifyUpdateEnergyScale();

    std::list<view::ViewInfoUpdater *> m_observers;

    utils::spectrum_t m_spectrum;
    utils::nuclides_t m_nuclides;
    utils::poly_t m_enpoly;

    idf::MethodPtr m_identifyMethod;
    utils::nl::NuclideLibraryPtr m_library;

    bool m_isStarted;

};

}
}

