#include "simulator.h"
#include <cassert>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "mathutils.h"

namespace dao {

Simulator::Simulator(const path_t &path, const double &countRate, QObject *parent)
    : DetectorAccess(parent)
    , m_mode(Modeling)
    , m_countRate(countRate)
    , m_timer(new QTimer(this))
    , m_fromModel(new SpectrumModeling)
    , m_fromFiles(new SpectrumMeasured)
{
    m_fromFiles->loadFromDirectory(path);
    connect(m_timer, &QTimer::timeout, this, &Simulator::onTimeout);
    m_timer->start(1000);
}

void Simulator::setActivity(size_t id, activity_t activity)
{
    assert(m_mode == Modeling);
    m_fromModel->update(id, activity);
}

void Simulator::setMode(Simulator::Mode mode)
{
    m_mode = mode;
}

void Simulator::changeSpectrumName(const std::string &name)
{
    assert(m_mode == Measured);
    m_fromFiles->changeCurrentName(name);
}

spectrum_t Simulator::spectrum() const
{
    return (m_mode == Modeling) ? m_fromModel->spectrum() : m_fromFiles->spectrum();
}

std::vector<std::string> Simulator::nuclideNames() const
{
    return m_fromModel->nuclideNames();
}

std::vector<std::string> Simulator::spectrumNames() const
{
    return m_fromFiles->names();
}

poly_t Simulator::energyPoly() const
{
    return m_fromModel->energyPoly();
}

double Simulator::countRate() const
{
    return m_countRate;
}

void Simulator::onTimeout()
{
    using namespace std::chrono;
    m_dataToRead.first = duration_cast<timestamp_t>(
                system_clock::now().time_since_epoch()
                );
    std::fill(m_dataToRead.second.begin(), m_dataToRead.second.end(), 0);

    auto tmp = mathutils::generatePortion(spectrum(), m_countRate);
    for (auto i = 0u; i < m_dataToRead.second.size(); i++) {
        m_dataToRead.second[i] += tmp[i];
    }

    emit readyRead(m_dataToRead);
}

}

