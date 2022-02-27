#pragma once

#include "types.h"
#include <iostream>

namespace model {

class NuclideLibrary
{
public:
    NuclideLibrary() = default;

    nuclides_t nuclides([[maybe_unused]]const probas_t &probas)
    {
        std::cout << "Return nuclides from library" << std::endl;
        return 0;
    }
};

using NuclideLibraryPtr = std::unique_ptr<NuclideLibrary>;

}

