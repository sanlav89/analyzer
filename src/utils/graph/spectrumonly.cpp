#include "spectrumonly.h"
#include <qwt_scale_engine.h>

namespace utils {
namespace graph {

SpectrumOnly::SpectrumOnly(const QColor &canvasColor1, const QColor &canvasColor2, QWidget *parent)
    : QwtPlot{parent}
{
    //  Widget settings
    setMinimumSize(800, 480);
    setAxisTitle(QwtPlot::yLeft, "Counts");
    setAxisTitle(QwtPlot::xBottom, "Energy [keV]");

    // Init energy scale
    m_energyValues.resize(SpectrumSize);
    m_countsValues.resize(SpectrumSize);

    // Axes font
    auto axisFont = QFont("Helvetica", 10);
    setAxisFont(QwtPlot::xBottom,  axisFont);
    setAxisFont(QwtPlot::yLeft, axisFont);

    // Canvas
    m_canvas = new Canvas(canvasColor1, canvasColor2, this);
    setCanvas(m_canvas);

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
    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->enableYMin(true);
    m_grid->enableX(true);
    m_grid->enableY(true);
    m_grid->setPen(gridPen);
    m_grid->attach(this);

    // Log Scale engine
    setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine);

    setAxisScale(QwtPlot::yLeft, 1, 10);
    replot();

}

void SpectrumOnly::setCurvePen(const QPen &pen)
{
    m_curve->setPen(pen);
    replot();
}

void SpectrumOnly::setGridPen(const QPen &pen)
{
    m_grid->setPen(pen);
    replot();
}

void SpectrumOnly::updateSpectrum(const spectrum_t &spectrum)
{
    assert(spectrum.size() == SpectrumSize);

    auto n = 0;
    auto ymax = 0;
    auto countsValue = [&n, &ymax, spectrum] {
        auto result = static_cast<double>(spectrum[n++]);
        if (result < LOG_MIN) {
            result = LOG_MIN;
        }
        if (result > ymax) {
            ymax = result;
        }
        return result;
    };
    std::generate(m_countsValues.begin(), m_countsValues.end(), countsValue);
    m_curve->setSamples(m_energyValues.data(), m_countsValues.data(), SpectrumSize);

    if (ymax < 2) {
        ymax = 2;
    }

    setAxisScale(QwtPlot::xBottom, 0, m_energyValues.back());
    setAxisScale(QwtPlot::yLeft, 1, ymax * 5);
    replot();
}

void SpectrumOnly::updateEnergyScale(const poly_t &enpoly)
{
    auto n = 1;
    auto energyValue = [&n, enpoly]() {
        qreal result = 0;
        for (auto i = 0u; i < enpoly.size(); i++) {
            result += enpoly[i] * std::pow(n, i);
        }
        n++;
        return result;
    };
    std::generate(m_energyValues.begin(), m_energyValues.end(), energyValue);
    setAxisScale(QwtPlot::xBottom, 0, m_energyValues.back());
    replot();
}

}
}
