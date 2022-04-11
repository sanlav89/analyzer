#pragma once

#include <iostream>
#include <map>
#include <list>
#include <utils/types.h>

namespace utils {
namespace nl {

class NuclideLibrary;
using NuclideLibraryPtr = std::shared_ptr<NuclideLibrary>;

class NuclideLibrary
{
public:

    static NuclideLibraryPtr instance(const std::string &filename);

    nuclides_t nuclides(const probas_t &probas) const;
    nuclides_t nuclidesAll() const;
    std::vector<std::string> nuclideNames() const;
    size_t numClasses() const;

private:
    static NuclideLibraryPtr m_instance;

    NuclideLibrary(const std::string &filename);
    NuclideLibrary(const NuclideLibrary &) = delete;
    void operator=(const NuclideLibrary &) = delete;

    std::map<int, nuclide_t> m_library;
};

}
}

