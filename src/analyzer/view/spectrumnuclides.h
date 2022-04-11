#pragma once

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_textlabel.h>
#include <qwt_text.h>
#include <qwt_plot_intervalcurve.h>
#include <qwt_interval_symbol.h>
#include <vector>
#include <utils/graph/spectrumonly.h>

namespace analyzer {
namespace view {

class SpectrumNuclides : public utils::graph::SpectrumOnly
{
    Q_OBJECT
public:
    SpectrumNuclides(const QColor &canvasColor1, const QColor &canvasColor2, QWidget *parent = nullptr);
    ~SpectrumNuclides();

    void updateNuclides(const utils::nuclides_t &nuclides);

private:

    QString taggedNuclideString(const utils::nuclide_t &nuclide);
    QString taggedString(const QString &info, const QColor &color);

    const size_t MaxNuclidesCount = 10;

    QwtText m_activityInfo;
    QwtPlotTextLabel *m_activityLabel;

    std::vector<QwtPlotIntervalCurve *> m_nuclideBars;
    std::vector<QwtIntervalSymbol *> m_nuclideBarsSymbols;

};

}
}
