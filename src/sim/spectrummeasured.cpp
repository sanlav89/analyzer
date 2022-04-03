#include "spectrummeasured.h"
#include "utils.h"
#include <QDir>

namespace sim {

using namespace utils;

SpectrumMeasured::SpectrumMeasured(const path_t &path)
{
    std::fill(m_currentSpectrum.begin(), m_currentSpectrum.end(), 0);
    loadFromDirectory(path);
}

void SpectrumMeasured::loadFromDirectory(const path_t &path)
{
    QDir directory(path.c_str());
    QStringList spectrumFiles = directory.entryList(QStringList() << "*.spe", QDir::Files);
    for (const auto &entry : spectrumFiles) {
        QString fileName = directory.path() + "/" + entry;
        m_spectrumMap[entry.toStdString()] = readFromSpeFile(fileName.toStdString());
        m_currentSpectrum = m_spectrumMap.at(entry.toStdString());
    }
}

void SpectrumMeasured::changeCurrentName(const std::string &name)
{
    assert(m_spectrumMap.find(name) != m_spectrumMap.end());
    m_currentSpectrum = m_spectrumMap.at(name);
}

spectrum_t SpectrumMeasured::spectrum() const
{
    return m_currentSpectrum;
}

std::vector<std::string> SpectrumMeasured::names() const
{
    std::vector<std::string> result;
    result.reserve(m_spectrumMap.size());
    for (const auto &pair : m_spectrumMap) {
        result.push_back(pair.first);
    }
    return result;
}

}
