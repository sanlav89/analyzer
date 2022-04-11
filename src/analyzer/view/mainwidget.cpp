#include "mainwidget.h"
#include <QGridLayout>
#include <qwt_plot.h>

namespace analyzer {
namespace view {

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    m_graph = new SpectrumNuclides(QColor(75, 75, 75), QColor(125, 125, 125), this);

    m_startBtn = new QPushButton("Start", this);
    m_pauseBtn = new QPushButton("Pause", this);
    m_clearBtn = new QPushButton("Clear", this);
    m_statusLbl = new QLabel(this);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_graph, 0, 0, 19, 20);
    mainLayout->addWidget(m_startBtn, 19, 0, 1, 1);
    mainLayout->addWidget(m_pauseBtn, 19, 1, 1, 1);
    mainLayout->addWidget(m_clearBtn, 19, 2, 1, 1);
    mainLayout->addWidget(m_statusLbl, 19, 3, 1, 17);
    setLayout(mainLayout);

    connect(m_startBtn, &QPushButton::clicked, this, &MainWidget::startButtonClicked);
    connect(m_pauseBtn, &QPushButton::clicked, this, &MainWidget::pauseButtonClicked);
    connect(m_clearBtn, &QPushButton::clicked, this, &MainWidget::clearButtonClicked);

}

void MainWidget::updateEnergyScale(const utils::poly_t &enpoly)
{
    m_graph->updateEnergyScale(enpoly);
}

void MainWidget::updateStatusMsg(const std::string &msg)
{
    m_statusLbl->setText(QString(msg.c_str()));
}

void MainWidget::setStartedButtonsState()
{
    m_startBtn->setEnabled(false);
    m_pauseBtn->setEnabled(true);
}

void MainWidget::setPausedButtonsState()
{
    m_startBtn->setEnabled(true);
    m_pauseBtn->setEnabled(false);
}

void MainWidget::updateSpectrum(const utils::spectrum_t &spectrum)
{
    m_graph->updateSpectrum(spectrum);
}

void MainWidget::updateNuclides(const utils::nuclides_t &nuclides)
{
    m_graph->updateNuclides(nuclides);
}

}
}
