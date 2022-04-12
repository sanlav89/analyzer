#pragma once

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <vector>
#include <utils/graph/canvas.h>
#include <utils/types.h>

namespace utils {
namespace graph {

class SpectrumOnly : public QwtPlot
{
    Q_OBJECT
public:
    SpectrumOnly(const QColor &canvasColor1, const QColor &canvasColor2, QWidget *parent = nullptr);
    ~SpectrumOnly() = default;

    void setCurvePen(const QPen &pen);
    void setGridPen(const QPen &pen);

    void updateSpectrum(const spectrum_t &spectrum);
    void updateEnergyScale(const poly_t &enpoly);

protected:
    Canvas *m_canvas;
    QwtPlotGrid *m_grid;
    QwtPlotCurve *m_curve;
    std::vector<qreal> m_energyValues;
    std::vector<qreal> m_countsValues;

};

}
}
