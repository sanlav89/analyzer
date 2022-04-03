#include "measured.h"
#include <QDir>
#include <cassert>
#include <utils/utils.h>

namespace sim {

namespace spectrum {

Measured::Measured(const utils::path_t &path)
{
    std::fill(m_currentSpectrum.begin(), m_currentSpectrum.end(), 0);
    loadFromDirectory(path);
}

void Measured::updateActivity(size_t, utils::activity_t)
{
    assert(false);
}

void Measured::updateName(const utils::name_t &name)
{
    assert(m_spectrumMap.find(name) != m_spectrumMap.end());
    m_currentSpectrum = m_spectrumMap.at(name);
}

utils::spectrum_t Measured::spectrum() const
{
    return m_currentSpectrum;
}

utils::poly_t Measured::energyPoly() const
{
    assert(false);
    return {};
}

utils::names_t Measured::names() const
{
    utils::names_t result;
    result.reserve(m_spectrumMap.size());
    for (const auto &pair : m_spectrumMap) {
        result.push_back(pair.first);
    }
    return result;
}

void Measured::loadFromDirectory(const utils::path_t &path)
{
    QDir directory(path.c_str());
    QStringList spectrumFiles = directory.entryList(QStringList() << "*.spe", QDir::Files);
    for (const auto &entry : spectrumFiles) {
        QString fileName = directory.path() + "/" + entry;
        m_spectrumMap[entry.toStdString()] = utils::readFromSpeFile(fileName.toStdString());
        m_currentSpectrum = m_spectrumMap.at(entry.toStdString());
    }
}

}

}
