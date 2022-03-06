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
using nuclides_t = int;
using activities_t = int;

using spectrum_t = std::array<sample_t, SpectrumSize>;
using data_t = std::pair<timestamp_t, spectrum_t>;

