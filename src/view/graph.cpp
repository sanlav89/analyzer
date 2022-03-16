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
    setCanvas(new GraphCanvas(QColor(75, 75, 75), QColor(125, 125, 125), this));

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
    auto curvePen = QPen(QColor(100, 255, 150), 1.5);
    m_curve = new QwtPlotCurve;
    m_curve->setStyle(curveStyle);
    m_curve->setPen(curvePen);
    m_curve->attach(this);

    // Activity info
    auto activityInfoFont = QFont("Consolas", 12, QFont::Normal);
    activityInfoFont.setBold(true);
    auto activityInfoRenderFlags = Qt::AlignRight | Qt::AlignTop;
    auto activityInfoTextColor = gridColor;
    auto activityInfoBorderPen = QPen(activityInfoTextColor, 1);
    auto activityInfoBorderRadius = 3;
    auto activityInfoBorderFill = activityInfoTextColor;
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
    m_activityLabel->setVisible(false);

    // Log Scale engine
    setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine);

    // Nuclidee lines bars
    for (auto i = 0u; i < MaxNuclidesCount; i++) {
        auto intervalSymbol = new QwtIntervalSymbol( QwtIntervalSymbol::Bar );
        intervalSymbol->setWidth(8); // should be something even
        m_nuclideBarsSymbols.push_back(intervalSymbol);
        auto intervalCurve = new QwtPlotIntervalCurve;
        intervalCurve->setSymbol(intervalSymbol);
        QColor c = Qt::white;
        c.setAlpha(0);
        intervalCurve->setPen(c, 0.0, Qt::NoPen);
        intervalCurve->setBrush(c);
        intervalCurve->attach(this);
        m_nuclideBars.push_back(intervalCurve);
    }

    setAxisScale(QwtPlot::yLeft, 1, 10);
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
    // Sort All Lines
    struct {
        bool operator()(line_t l1, line_t l2) const
        {
            return l1.intensity < l2.intensity;
        }
    } less;

    // Disable all markers
    for (auto intervalCurve : m_nuclideBars) {
        intervalCurve->setVisible(false);
    }

    // Enable first 10 markers
    QVector<QwtIntervalSample> rangeData;
    rangeData.reserve(10);

    double ymax = axisScaleDiv(QwtPlot::yLeft).upperBound();

    int ind = 0;
    for (const auto &nuclide : nuclides) {
        auto it = std::max_element(nuclide.lines.begin(), nuclide.lines.end(), less);
        double intencityMax = it->intensity;
        rangeData.clear();
        for (const auto &line : nuclide.lines) {
            auto x = line.energy;
            auto y = line.intensity / intencityMax * ymax;
            rangeData.push_back(QwtIntervalSample(x, 0.5, y));
        }
        m_nuclideBars[ind]->setSamples(rangeData);
        QColor c = Qt::GlobalColor(nuclide.color);
        m_nuclideBarsSymbols[ind]->setPen(c, 1.5);
        c.setAlpha(0);
        m_nuclideBars[ind]->setPen(c, 0.0, Qt::NoPen);
        m_nuclideBars[ind]->setBrush(c);
        m_nuclideBars[ind]->setSymbol(m_nuclideBarsSymbols[ind]);
        m_nuclideBars[ind]->setVisible(true);
        ind++;
    }

    // Update Activities
    if (nuclides.empty()) {
        m_activityLabel->setVisible(false);
    } else {
        auto activityStr = taggedString("Activities : ", m_activityInfo.color());
        for (const auto &nuclide : nuclides) {
            activityStr.append(taggedNuclideString(nuclide));
        }
        m_activityInfo.setText(activityStr);
        m_activityLabel->setText(m_activityInfo);
        m_activityLabel->setVisible(true);
    }

    replot();
}

void Graph::updateEnergyScale(const poly_t &enpoly)
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
