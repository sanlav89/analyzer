#pragma once

#include "graph.h"

namespace view {

class DetectorGraph : public Graph
{
    Q_OBJECT
public:
    DetectorGraph(QWidget *parent = nullptr);
    ~DetectorGraph() = default;
//    void updateSpectrum(const spectrum_t &spectrum);

};

}
