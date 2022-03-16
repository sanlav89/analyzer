#include "simulatoraccess.h"

namespace dao {

SimulatorAccess::SimulatorAccess(QObject *parent)
    : DetectorAccess(parent)
{
    m_simulator = new Simulator("./data", 100, this);
    m_simulator->setMode(Simulator::Measured);
    connect(m_simulator, &Simulator::readyRead, this, &SimulatorAccess::readyRead);
}

}
