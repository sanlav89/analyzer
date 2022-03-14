#pragma once

#include "types.h"
#include <iostream>
#include <map>

namespace model {

class NuclideLibrary
{
public:
    NuclideLibrary();
    nuclides_t nuclides(const probas_t &probas);

private:
    std::map<int, nuclide_t> m_library;
};

using NuclideLibraryPtr = std::unique_ptr<NuclideLibrary>;

}

