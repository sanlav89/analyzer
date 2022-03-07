#include "controller.h"

namespace ctrl {

Controller::Controller(ModelPtr model, ViewPtr view, QObject *parent)
    : QObject(parent)
    , m_model(std::move(model))
    , m_view(view)
{
    connect(m_view, &View::startButtonClicked, this, &Controller::onStartBtn);
    connect(m_view, &View::pauseButtonClicked, this, &Controller::onPauseBtn);
    connect(m_view, &View::clearButtonClicked, this, &Controller::onClearBtn);
    m_view->show();
}

void Controller::setDetector(DetectorPtr detector)
{
    m_detector = std::move(detector);
}

void Controller::execute()
{
    assert(m_detector.get() != nullptr);
    m_model->setEnPoly({-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10});
    m_detector->connect();
    m_model->receiveNewSpectrumData(m_detector->read().second);
}

void Controller::onStartBtn()
{
    m_view->setStartedButtonsState();
}

void Controller::onPauseBtn()
{
    m_view->setPausedButtonsState();
}

void Controller::onClearBtn()
{
    m_model->clearSpectrum();
}

}
