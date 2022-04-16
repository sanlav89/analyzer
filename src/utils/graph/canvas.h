#pragma once

#include <qwt_plot_canvas.h>
#include <qwt_painter.h>

namespace utils {
namespace graph {

class Canvas : public QwtPlotCanvas
{
public:
    Canvas(QColor beginColor, QColor endColor, QwtPlot *plot = nullptr);
    void setupPalette(QColor beginColor, QColor endColor);
};

}
}



