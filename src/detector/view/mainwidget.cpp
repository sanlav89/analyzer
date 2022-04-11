#include "mainwidget.h"
#include <QGridLayout>

namespace detector {
namespace view {

MainWidget::MainWidget(
        const utils::poly_t &energyPoly,
        const utils::names_t &nuclidesNames,
        const utils::names_t &measuredNames,
        QWidget *parent)
    : QWidget(parent)
{
    m_graph = new utils::graph::SpectrumOnly(QColor(175, 175, 175), QColor(225, 225, 225), this);
    m_graph->updateEnergyScale(energyPoly);

    m_modelingRaB = new QRadioButton("Spectrum Model");
    m_measuredRaB = new QRadioButton("Real Measurements");
    m_modelingRaB->setChecked(true);
    connect(m_modelingRaB, &QRadioButton::toggled, this, &MainWidget::onRadioButtonToggled);

    m_modelingWidget = new ModelingWidget(nuclidesNames, this);
    m_modelingWidget->setMaximumHeight(420);
    connect(m_modelingWidget, &ModelingWidget::activityChanged, this, &MainWidget::activityChanged);

    m_measuredWidget = new MeasuredWidget(measuredNames, this);
    connect(m_measuredWidget, &MeasuredWidget::nameChanged, this, &MainWidget::nameChanged);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_graph, 0, 0, 10, 10);
    mainLayout->addWidget(m_modelingRaB, 0, 10, 1, 5);
    mainLayout->addWidget(m_modelingWidget, 1, 10, 5, 5);
    mainLayout->addWidget(m_measuredRaB, 6, 10, 1, 5);
    mainLayout->addWidget(m_measuredWidget, 7, 10, 3, 5);
    setLayout(mainLayout);
}

void MainWidget::updateSpectrum(const utils::spectrum_t &spectrum)
{
    m_graph->updateSpectrum(spectrum);
}

void MainWidget::setEnabledWidgets(bool modeling, bool measured)
{
    m_modelingWidget->setEnabled(modeling);
    m_measuredWidget->setEnabled(measured);
}

void MainWidget::onRadioButtonToggled()
{
    auto mode = m_modelingRaB->isChecked() ? model::ModeModeling : model::ModeMeasured;
    emit modeChanged(mode);
}

}
}


