#pragma once

#include "types.h"

namespace utils {

using separator_t = char;

bool read_features_csv(std::istream& stream, spectrum_t& spectrum, separator_t sep = ',');

}

