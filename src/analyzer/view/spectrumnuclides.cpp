#include "spectrumnuclides.h"
#include <cassert>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_scale_engine.h>
#include <algorithm>
#include <utils/graph/canvas.h>

namespace analyzer {
namespace view {

SpectrumNuclides::SpectrumNuclides(const QColor &canvasColor1, const QColor &canvasColor2, QWidget *parent)
    : SpectrumOnly{canvasColor1, canvasColor2, parent}
{
    // Canvas
    m_canvas->setupPalette(canvasColor1, canvasColor2);

    // Grid
    auto gridColor = QColor(200, 200, 200);
    gridColor.setAlpha(50);
    auto gridPen = QPen(gridColor, 0.5);
    m_grid->setPen(gridPen);

    // Activity info
    auto activityInfoFont = QFont("Consolas", 12, QFont::Normal);
    activityInfoFont.setBold(true);
    auto activityInfoRenderFlags = Qt::AlignRight | Qt::AlignTop;
    auto activityInfoTextColor = QColor(200, 200, 200);
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

    // Nuclide lines bars
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

    replot();
}

SpectrumNuclides::~SpectrumNuclides()
{
}

void SpectrumNuclides::updateNuclides(const utils::nuclides_t &nuclides)
{
    // Sort All Lines
    struct {
        bool operator()(utils::line_t l1, utils::line_t l2) const
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

QString SpectrumNuclides::taggedNuclideString(const utils::nuclide_t &nuclide)
{
    return taggedString(
                QString::asprintf(
                    "<br>%7s : %.3f", nuclide.name.c_str(), nuclide.activity
                    ),
                QColor(Qt::GlobalColor(nuclide.color))
                );
}

QString SpectrumNuclides::taggedString(const QString &info, const QColor &color)
{
    auto result = QString("<font color=\"%1\">%2</font>")
            .arg(color.name(), info);
    return result;
}

}
}
