#include "simulator.h"
#include <cassert>
#include <fstream>
#include <algorithm>
#include <iostream>

namespace dao {

Simulator::Simulator(const filelist_t &filelist)
    : m_filelist(filelist)
{
    assert(filelist.size() > 0);
    m_spectrums.reserve(filelist.size());
}

void Simulator::connect()
{
    for (const auto &filename :  m_filelist) {
        m_spectrums.push_back(readFromBinaryFile(filename));
    }
}

data_t Simulator::read()
{
    spectrum_t spectrum;

    auto n = 0;

    auto genSample = [&n, this] {
        sample_t result = 0;
        for (auto spectrum : m_spectrums) {
            result += spectrum[n];
        }
        result /= m_spectrums.size();
        n++;
        return result;
    };

    std::generate(spectrum.begin(), spectrum.end(), genSample);

    using namespace std::chrono;
    timestamp_t ms = duration_cast<timestamp_t>(
                system_clock::now().time_since_epoch()
                );
    return data_t{ms, spectrum};
}

void Simulator::disconnect()
{
}

spectrum_t Simulator::readFromBinaryFile(const filename_t &filename)
{
    spectrum_t result;
    std::ifstream input(filename, std::ios::in | std::ios::binary);
    char *buffer = reinterpret_cast<char *>(result.data());
    input.read(buffer, sizeof(sample_t) * (SpectrumSize - 1));
    result[SpectrumSize - 1] = 0;
    return result;
}

}

