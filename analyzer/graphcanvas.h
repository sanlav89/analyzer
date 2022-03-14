#pragma once

#include <qwt_plot_canvas.h>
#include <qwt_painter.h>

namespace view {

class GraphCanvas : public QwtPlotCanvas
{
public:
    GraphCanvas(QColor beginColor, QColor endColor, QwtPlot *plot = nullptr);

private:
    void setupPalette(QColor beginColor, QColor endColor);
};

}



