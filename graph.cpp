#include "graph.h"
#include <cassert>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_scale_engine.h>

namespace view {

Graph::Graph(const enpoly_t &enpoly, QWidget *parent)
    : QwtPlot(parent)
{
    // Init energy scale
    m_energyValues.resize(SpectrumSize);
    m_countsValues.resize(SpectrumSize);
    updateEnergyScale(enpoly);

    // Axes font
    auto axisFont = QFont("Helvetica", 10);
    setAxisFont(QwtPlot::xBottom,  axisFont);
    setAxisFont(QwtPlot::yLeft, axisFont);

    // Background
    auto bg = QBrush(QColor(50, 50, 100));
    QPalette pal;
    pal.setBrush(QPalette::Window, bg);
    setPalette(pal);

    // Grid
    auto grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->enableX(false);
    grid->enableY(false);
    grid->attach(this);

    // Spectrum Curve
    auto curveStyle = QwtPlotCurve::Lines;
    auto curvePen = QPen(Qt::cyan, 1);
    m_curve = new QwtPlotCurve;
    m_curve->setStyle(curveStyle);
    m_curve->setPen(curvePen);
    m_curve->attach(this);

    // Markers
    auto markerPen = QPen(QColor(200, 150, 0), 0, Qt::SolidLine);
    auto markerSymbolType = QwtSymbol::Diamond;
    auto markerSymbolColorBorder = QPen(Qt::yellow);
    auto markerSymbolColorFill = QBrush(Qt::cyan);
    auto markerSymbolSize = QSize(10, 10);
    auto markerLineStyle = QwtPlotMarker::Cross;
    auto markerAlignment = Qt::AlignLeft | Qt::AlignTop;
    m_markers.reserve(MaxMarkersCount);
    for (auto i = 0; i < MaxMarkersCount; i++) {
        auto marker = new QwtPlotMarker;
        marker->setLineStyle(markerLineStyle);
        marker->setLabelAlignment(markerAlignment);
        marker->setLinePen(markerPen);
        marker->setSymbol(new QwtSymbol(markerSymbolType, markerSymbolColorFill,
                                        markerSymbolColorBorder, markerSymbolSize));
        marker->attach(this);
        m_markers.push_back(marker);
    }

    // Activity info
    auto activityInfoFont = QFont("Consolas", 9, QFont::Normal);
    auto activityInfoRenderFlags = Qt::AlignLeft;
    auto activityInfoTextColor = QColor(250, 200, 100);
    auto activityInfoBorderPen = QPen(QColor(250, 200, 100), 1);
    auto activityInfoBorderRadius = 3;
    auto activityInfoBorderFill = QColor(60, 60, 100);
    activityInfoBorderFill.setAlpha(50);
    m_activityInfo.setFont(activityInfoFont);
    m_activityInfo.setRenderFlags(activityInfoRenderFlags);
    m_activityInfo.setColor(activityInfoTextColor);
    m_activityInfo.setBorderPen(activityInfoBorderPen);
    m_activityInfo.setBorderRadius(activityInfoBorderRadius);
    m_activityInfo.setBackgroundBrush(QBrush(activityInfoBorderFill));

    // Log Scale engine
    setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine);

    replot();
}

Graph::~Graph()
{
}

void Graph::updateSpectrum(const spectrum_t &spectrum)
{
    assert(spectrum.size() == SpectrumSize);
    auto n = 0;
    auto countsValue = [&n, spectrum] {
        auto result = static_cast<double>(spectrum[n++]);
        if (result < LOG_MIN) {
            result = LOG_MIN;
        }
        return result;
    };
    std::generate(m_countsValues.begin(), m_countsValues.end(), countsValue);
    m_curve->setSamples(m_energyValues.data(), m_countsValues.data(), SpectrumSize);
    replot();
}

void Graph::updateActivities([[maybe_unused]]const activities_t &activities)
{
    replot();
}

void Graph::updateNuclides([[maybe_unused]]const nuclideid_t &nuclides)
{
    replot();
}

void Graph::updateEnergyScale(const enpoly_t &enpoly)
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
}

}
