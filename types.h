#pragma once

#include <memory>
#include <vector>
#include <array>
#include <chrono>

const int SpectrumSize = 1024;

using sample_t = int;
using proba_t = float;
using probas_t = std::vector<proba_t>;
using timestamp_t = std::chrono::milliseconds;
using nuclideid_t = int;
using activityval_t = double;
using intensity_t = double;
using energy_t = double;
using enpoly_t = std::vector<double>;

struct line_t {
    energy_t energy;
    intensity_t intensity;
};

struct nuclide_t {
    std::string name;
    std::vector<line_t> lines;
};

struct activity_t {
    std::string name;
    activityval_t activity;
};

using nuclides_t = std::vector<nuclide_t>;
using activities_t = std::vector<activity_t>;

using spectrum_t = std::array<sample_t, SpectrumSize>;
using data_t = std::pair<timestamp_t, spectrum_t>;

