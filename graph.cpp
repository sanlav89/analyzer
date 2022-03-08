#include "graph.h"
#include <cassert>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_scale_engine.h>
#include <algorithm>
#include "graphcanvas.h"

namespace view {

Graph::Graph(QWidget *parent)
    : QwtPlot(parent)
{
    //  Widget settings
    setMinimumSize(800, 480);

    // Init energy scale
    m_energyValues.resize(SpectrumSize);
    m_countsValues.resize(SpectrumSize);

    // Axes font
    auto axisFont = QFont("Helvetica", 10);
    setAxisFont(QwtPlot::xBottom,  axisFont);
    setAxisFont(QwtPlot::yLeft, axisFont);

    // Canvas
    setCanvas(new GraphCanvas(QColor(25, 25, 25), QColor(75, 75, 75), this));

    // Grid
    auto gridColor = QColor(200, 200, 200);
    gridColor.setAlpha(50);
    auto gridPen = QPen(gridColor, 0.5);
    auto grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->enableX(true);
    grid->enableY(true);
    grid->setPen(gridPen);
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
    auto markerSymbolType = QwtSymbol::NoSymbol;
    auto markerSymbolColorBorder = QPen(Qt::yellow);
    auto markerSymbolColorFill = QBrush(Qt::cyan);
    auto markerSymbolSize = QSize(10, 10);
    auto markerLineStyle = QwtPlotMarker::VLine;
    auto markerAlignment = Qt::AlignLeft | Qt::AlignTop;
    m_markers.reserve(MaxMarkersCount);
    for (auto i = 0u; i < MaxMarkersCount; i++) {
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
    auto activityInfoFont = QFont("Consolas", 12, QFont::Normal);
    activityInfoFont.setBold(true);
    auto activityInfoRenderFlags = Qt::AlignRight | Qt::AlignTop;
    auto activityInfoTextColor = QColor(200, 200, 200);
    auto activityInfoBorderPen = QPen(QColor(200, 200, 200), 1);
    auto activityInfoBorderRadius = 3;
    auto activityInfoBorderFill = QColor(200, 200, 200);
    activityInfoBorderFill.setAlpha(75);
    m_activityInfo.setFont(activityInfoFont);
    m_activityInfo.setRenderFlags(activityInfoRenderFlags);
    m_activityInfo.setColor(activityInfoTextColor);
    m_activityInfo.setBorderPen(activityInfoBorderPen);
    m_activityInfo.setBorderRadius(activityInfoBorderRadius);
    m_activityInfo.setBackgroundBrush(QBrush(activityInfoBorderFill));
    m_activityLabel = new QwtPlotTextLabel;
    m_activityLabel->attach(this);
    m_activityLabel->setText(m_activityInfo);

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

void Graph::updateNuclides(const nuclides_t &nuclides)
{
    // All lines
    struct lineinfo_t {
        std::string name;
        color_t color;
        line_t line;
    };
    std::vector<lineinfo_t> allLines;
    allLines.reserve(50);
    for (const auto &nuclide : nuclides) {
        for (const auto &line : nuclide.lines) {
            allLines.push_back({nuclide.name, nuclide.color, line});
        }
    }

    // Sort All Lines
    struct {
        bool operator()(lineinfo_t l1, lineinfo_t l2) const
        {
            return l1.line.intensity > l2.line.intensity;
        }
    } greater;
    std::sort(allLines.begin(), allLines.end(), greater);

    // Disable all markers
    for (auto marker : m_markers) {
        marker->setVisible(false);
    }

    // Enable first 10 markers
    for (auto i = 0u; i < allLines.size(); i++) {
        if (i >= MaxMarkersCount || allLines[i].line.intensity < 1) {
            break;
        }
        m_markers[i]->setValue(allLines[i].line.energy, 1);
        m_markers[i]->setLinePen(Qt::GlobalColor(allLines[i].color), 0, Qt::SolidLine);
        m_markers[i]->setVisible(true);
    }

    // Update Activities
    auto activityStr = taggedString("Activities : ", m_activityInfo.color());
    for (const auto &nuclide : nuclides) {
        activityStr.append(taggedNuclideString(nuclide));
    }
    m_activityInfo.setText(activityStr);
    m_activityLabel->setText(m_activityInfo);

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

QString Graph::taggedNuclideString(const nuclide_t &nuclide)
{
    return taggedString(
                QString::asprintf(
                    "<br>%7s : %.3f", nuclide.name.c_str(), nuclide.activity
                    ),
                QColor(Qt::GlobalColor(nuclide.color))
                );
}

QString Graph::taggedString(const QString &info, const QColor &color)
{
    auto result = QString("<font color=\"%1\">%2</font>")
            .arg(color.name(), info);
    return result;
}

}
