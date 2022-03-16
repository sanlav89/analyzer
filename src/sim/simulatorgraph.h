#pragma once

#include "graph.h"

namespace view {

class SimulatorGraph : public Graph
{
    Q_OBJECT
public:
    SimulatorGraph(QWidget *parent = nullptr);
    ~SimulatorGraph() = default;
//    void updateSpectrum(const spectrum_t &spectrum);

};

}
