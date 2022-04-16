#pragma once

#include <QWidget>
#include <QRadioButton>
#include <view/measuredwidget.h>
#include <view/modelingwidget.h>
#include <utils/graph/spectrumonly.h>
#include <model/modes.h>

namespace detector {
namespace view {

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(
            const utils::poly_t &energyPoly,
            const utils::names_t &nuclidesNames,
            const utils::names_t &measuredNames,
            QWidget *parent = nullptr
            );

    void updateSpectrum(const utils::spectrum_t &spectrum);
    void setEnabledWidgets(bool modeling, bool measured);

private:
    utils::graph::SpectrumOnly *m_graph;
    ModelingWidget *m_modelingWidget;
    MeasuredWidget *m_measuredWidget;
    QRadioButton *m_modelingRaB;
    QRadioButton *m_measuredRaB;

signals:
    void modeChanged(int);
    void activityChanged(int, qreal);
    void nameChanged(const std::string &);

private slots:
    void onRadioButtonToggled();

};

}
}
