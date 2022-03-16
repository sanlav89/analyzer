#pragma once

#include "dao/detectoraccess.h"
#include "sim/simulator.h"

namespace dao {

using namespace sim;

class SimulatorAccess : public DetectorAccess
{
    Q_OBJECT
public:
    explicit SimulatorAccess(QObject *parent = nullptr);

private:
    Simulator *m_simulator;

};

}

