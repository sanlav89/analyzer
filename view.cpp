#include "view.h"
#include <QVBoxLayout>

namespace view {

View::View(QWidget *parent)
    : QWidget(parent)
    , m_state(Paused)
{
    m_startBtn = new QPushButton("Start", this);
    m_pauseBtn = new QPushButton("Pause", this);
    m_clearBtn = new QPushButton("Clear", this);

    m_statusLbl   = new QLabel("", this);
    m_activityLbl = new QLabel("", this);
    m_spectrumLbl = new QLabel("", this);
    m_nuclidesLbl = new QLabel("", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_startBtn, 1);
    mainLayout->addWidget(m_pauseBtn, 1);
    mainLayout->addWidget(m_clearBtn, 1);
    mainLayout->addWidget(m_statusLbl, 1);
    mainLayout->addWidget(m_activityLbl, 1);
    mainLayout->addWidget(m_spectrumLbl, 1);
    mainLayout->addWidget(m_nuclidesLbl, 1);
    setLayout(mainLayout);

    connect(m_startBtn, &QPushButton::clicked, this, &View::onStartBtn);
    connect(m_pauseBtn, &QPushButton::clicked, this, &View::onPauseBtn);
    connect(m_clearBtn, &QPushButton::clicked, this, &View::onClearBtn);

}

void View::updateSpectrum(const data_t &data)
{
    m_spectrumLbl->setText(QString::asprintf("Spectrum: %d", data));
}

void View::updateNuclides(const nuclides_t &nuclides)
{
    m_nuclidesLbl->setText(QString::asprintf("Nuclides: %d", nuclides));
}

void View::updateActivities(const activities_t &activities)
{
    m_activityLbl->setText(QString::asprintf("Activities: %d", activities));
}

void View::updateState()
{
    switch (m_state) {
    case Paused:
        m_statusLbl->setText("Paused >");
        break;
    case Started:
        m_statusLbl->setText("Started ||");
        break;
    }
}

void View::onStartBtn()
{
    m_state = Started;
    updateState();
}

void View::onPauseBtn()
{
    m_state = Paused;
    updateState();
}

void View::onClearBtn()
{
    m_statusLbl->setText("Cleared");
}

}
