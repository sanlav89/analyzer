#include "controller.h"
#include "dao/tcpaccess.h"

namespace ctrl {

Controller::Controller(Analyzer *model, View *view, QObject *parent)
    : QObject(parent)
    , m_model(std::move(model))
    , m_view(view)
    , m_detector(new TcpAccess(9999, this))
{
    m_model->setEnPoly({-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10});

    connect(m_view, &View::startButtonClicked, this, &Controller::onStartBtn);
    connect(m_view, &View::pauseButtonClicked, this, &Controller::onPauseBtn);
    connect(m_view, &View::clearButtonClicked, this, &Controller::onClearBtn);

    // Init view state
    m_view->setPausedButtonsState();
    m_view->show();

    // Init model state
    m_model->setIsStarted(false);

    // Connection with detector
    connect(m_detector, &DetectorAccess::readyRead, this, &Controller::onDetectorReadyRead);
}

void Controller::onStartBtn()
{
    m_view->setStartedButtonsState();
    m_model->setIsStarted(true);
}

void Controller::onPauseBtn()
{
    m_view->setPausedButtonsState();
    m_model->setIsStarted(false);
}

void Controller::onClearBtn()
{
    m_model->clearSpectrum();
}

void Controller::onDetectorReadyRead(data_t data)
{
    m_model->receiveNewSpectrumData(data.second);
}

}
