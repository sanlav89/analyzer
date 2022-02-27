#pragma once

#include "nuclidelibrary.h"
#include "identifymethod.h"

using namespace idf;

namespace model {

activities_t calcActivities(const spectrum_t &spectrum, const nuclides_t &nuclides);

class Model
{
public:
    Model();

    void accum(const spectrum_t &spectrum);
    void clear();

private:

    spectrum_t m_spectrum;
    IdentifyMethodPtr m_identifyMethod;
    NuclideLibraryPtr m_library;

};

using ModelPtr = std::unique_ptr<Model>;

}

