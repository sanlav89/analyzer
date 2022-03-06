#pragma once

#include "nuclidelibrary.h"
#include "identifymethod.h"
#include "detector.h"

using namespace idf;
using namespace dao;

namespace model {

activities_t calcActivities(const spectrum_t &spectrum, const nuclides_t &nuclides);

class Model
{
public:
    Model();

    spectrum_t spectrum() const;
    nuclides_t nuclides() const;
    activities_t activities() const;
    enpoly_t enpoly() const;

private:

    spectrum_t m_spectrum;
    IdentifyMethodPtr m_identifyMethod;
    DetectorPtr m_detector;
    NuclideLibraryPtr m_library;
    enpoly_t m_enpoly;

};

using ModelPtr = std::unique_ptr<Model>;

}

