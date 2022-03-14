#include "simulator.h"
#include <cassert>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstdlib>

namespace dao {

Simulator::Simulator(const filelist_t &filelist, const double &countRate, QObject *parent)
    : DetectorAccess(parent)
    , m_timer(new QTimer(this))
    , m_countRate(countRate)
{
    assert(filelist.size() > 0);
    m_spectrums.reserve(filelist.size());
    for (const auto &filename :  filelist) {
        m_spectrums.push_back(readFromBinaryFile(filename));
    }
    connect(m_timer, &QTimer::timeout, this, &Simulator::onTimeout);
    m_timer->start(1000);
}

data_t Simulator::read()
{
    return m_dataToRead;
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

void Simulator::onTimeout()
{
    using namespace std::chrono;
    m_dataToRead.first = duration_cast<timestamp_t>(
                system_clock::now().time_since_epoch()
                );
    std::fill(m_dataToRead.second.begin(), m_dataToRead.second.end(), 0);

    for (const auto &spectrum : m_spectrums) {
        int countRate = static_cast<double>(std::rand()) / RAND_MAX * m_countRate + m_countRate / 2;
        auto score = std::accumulate(spectrum.begin(), spectrum.end(), 0);
        for (auto i = 0; i < countRate; i++) {
            int point = static_cast<double>(std::rand()) / RAND_MAX * score;;
            int left = 0;
            for (auto j = 0u; j < spectrum.size(); j++) {
                if (point >= left && point < left + spectrum[j]) {
                    m_dataToRead.second[j] += 1;
                    break;
                } else {
                    left += spectrum[j];
                }
            }
        }
    }
    emit readyRead();
}

}

