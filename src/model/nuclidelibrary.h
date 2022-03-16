#pragma once

#include "utils/types.h"
#include <iostream>
#include <map>
#include <list>

namespace model {

using namespace utils;

class NuclideLibrary
{
public:
    NuclideLibrary(const std::string &filename);
    nuclides_t nuclides(const probas_t &probas) const;
    nuclides_t nuclidesAll() const;
    std::vector<std::string> nuclideNames() const;

private:
    std::map<int, nuclide_t> m_library;
};

using NuclideLibraryPtr = std::unique_ptr<NuclideLibrary>;

}

