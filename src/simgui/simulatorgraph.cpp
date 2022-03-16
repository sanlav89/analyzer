#include "simulatorgraph.h"
#include "graphcanvas.h"
#include <qwt_plot_grid.h>

namespace view {

SimulatorGraph::SimulatorGraph(QWidget *parent)
    : Graph(parent)
{
    // Canvas
    setCanvas(new GraphCanvas(QColor(175, 175, 175), QColor(225, 225, 225), this));

    // Spectrum Curve
    auto curveStyle = QwtPlotCurve::Lines;
    auto curvePen = QPen(QColor(100, 100, 250), 1.5);
    m_curve = new QwtPlotCurve;
    m_curve->setStyle(curveStyle);
    m_curve->setPen(curvePen);
    m_curve->attach(this);

    // Grid
    auto gridColor = QColor(250, 250, 250);
    auto gridPen = QPen(gridColor, 0.5);
    auto grid = new QwtPlotGrid;
    grid->setPen(gridPen);
    grid->attach(this);
}

}
