#pragma once

#include "types.h"
#include <iostream>

namespace model {

class NuclideLibrary
{
public:
    NuclideLibrary();
    nuclides_t nuclides(const probas_t &probas);
};

using NuclideLibraryPtr = std::unique_ptr<NuclideLibrary>;

}

