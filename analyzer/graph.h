#pragma once

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_textlabel.h>
#include <qwt_text.h>
#include <qwt_plot_intervalcurve.h>
#include <qwt_interval_symbol.h>
#include <vector>
#include "view.h"

namespace view {

class Graph : public QwtPlot
{
    Q_OBJECT
public:
    Graph(QWidget *parent = nullptr);
    ~Graph();

    void updateSpectrum(const spectrum_t &spectrum);
    void updateNuclides(const nuclides_t &nuclides);
    void updateEnergyScale(const enpoly_t &enpoly);

private:

    QString taggedNuclideString(const nuclide_t &nuclide);
    QString taggedString(const QString &info, const QColor &color);

    const size_t MaxNuclidesCount = 10;

    QwtPlotCurve *m_curve;
    QwtText m_activityInfo;
    QwtPlotTextLabel *m_activityLabel;
    std::vector<qreal> m_energyValues;
    std::vector<qreal> m_countsValues;

    std::vector<QwtPlotIntervalCurve *> m_nuclideBars;
    std::vector<QwtIntervalSymbol *> m_nuclideBarsSymbols;

};

}