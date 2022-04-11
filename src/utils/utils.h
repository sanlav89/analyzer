#pragma once

#include <map>
#include "types.h"

namespace utils {

using separator_t = char;

bool read_features_csv(std::istream& stream, spectrum_t& spectrum, separator_t sep = ',');

spectrum_t readFromSpeFile(const filename_t &filename);

std::map<name_t, spectrum_t> loadFromDirectory(const utils::path_t &path);

}

