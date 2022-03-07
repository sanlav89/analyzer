#include "view.h"
#include <QGridLayout>
#include <qwt_plot.h>

namespace view {

View::View(QWidget *parent)
    : QWidget(parent)
{
    m_graph = new Graph({0, 1}, this);

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

    connect(m_startBtn, &QPushButton::clicked, this, &View::onStartBtn);
    connect(m_pauseBtn, &QPushButton::clicked, this, &View::onPauseBtn);
    connect(m_clearBtn, &QPushButton::clicked, this, &View::onClearBtn);

}

void View::updateEnergyScale(const enpoly_t &enpoly)
{
    m_graph->updateEnergyScale(enpoly);
}

void View::updateSpectrum([[maybe_unused]]const spectrum_t &spectrum)
{
    m_graph->updateSpectrum(spectrum);
}

void View::updateNuclides([[maybe_unused]]const nuclides_t &nuclides)
{
    m_graph->updateNuclides(nuclides);
}

void View::updateActivities([[maybe_unused]]const activities_t &activities)
{
    m_graph->updateActivities(activities);
}

void View::onStartBtn()
{
    m_statusLbl->setText("Started ||");
}

void View::onPauseBtn()
{
    m_statusLbl->setText("Paused >");
}

void View::onClearBtn()
{
    m_statusLbl->setText("Cleared");
}

}
