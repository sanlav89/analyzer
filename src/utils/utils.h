#pragma once

#include <map>
#include "types.h"

namespace utils {

spectrum_t readFromSpeFile(const filename_t &filename);

std::map<name_t, spectrum_t> loadFromDirectory(const utils::path_t &path);

}

