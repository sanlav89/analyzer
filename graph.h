#pragma once

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_textlabel.h>
#include <qwt_text.h>
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
    void updateActivities(const activities_t &activities);
    void updateNuclides(const nuclides_t &nuclides);
    void updateEnergyScale(const enpoly_t &enpoly);

private:

    const size_t MaxMarkersCount = 10;

    QwtPlotCurve *m_curve;
    QwtText m_activityInfo;
    QwtPlotTextLabel *m_activityLabel;
    std::vector<QwtPlotMarker *> m_markers;

    std::vector<qreal> m_energyValues;
    std::vector<qreal> m_countsValues;

};

}
