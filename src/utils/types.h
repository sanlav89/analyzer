#pragma once

#include <memory>
#include <vector>
#include <array>
#include <chrono>
#include <string>

namespace utils {

const int SpectrumSize = 1024;

using sample_t = int;
using proba_t = float;
using probas_t = std::vector<proba_t>;
using timestamp_t = std::chrono::milliseconds;
using nuclideid_t = int;
using activity_t = double;
using intensity_t = double;
using energy_t = double;
using poly_t = std::vector<double>;
using color_t = int;
using path_t = std::string;
using name_t = std::string;
using names_t = std::vector<std::string>;

struct line_t {
    energy_t energy;
    intensity_t intensity;
};

struct nuclide_t {
    std::string name;
    color_t color;
    activity_t activity;
    std::vector<line_t> lines;
};

using nuclides_t = std::vector<nuclide_t>;
using spectrum_t = std::array<sample_t, SpectrumSize>;
using data_t = std::pair<timestamp_t, spectrum_t>;

using filename_t  = std::string;
using filelist_t = std::vector<filename_t>;

}

