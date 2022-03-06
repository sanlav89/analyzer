#pragma once

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_textlabel.h>
#include <qwt_text.h>
#include <vector>
#include "iview.h"

namespace view {

class Graph : public QwtPlot, public IView
{
    Q_OBJECT
public:
    Graph(const enpoly_t &enpoly = enpoly_t{0, 1}, QWidget *parent = nullptr);
    ~Graph();

    void updateSpectrum(const spectrum_t &spectrum) override;
    void updateActivities(const activities_t &activities) override;
    void updateNuclides(const nuclides_t &nuclides) override;
    void updateEnergyScale(const enpoly_t &enpoly) override;

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
