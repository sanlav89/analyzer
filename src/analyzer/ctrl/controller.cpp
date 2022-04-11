#include "controller.h"

namespace analyzer {
namespace ctrl {

Controller::Controller(model::Analyzer *model, view::MainWidget *view, QObject *parent)
    : QObject{parent}
    , m_model{model}
    , m_view{view}
    , m_receiver{nullptr}
{
    m_model->setEnPoly({-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10});

    connect(m_view, &view::MainWidget::startButtonClicked, this, &Controller::onStartBtn);
    connect(m_view, &view::MainWidget::pauseButtonClicked, this, &Controller::onPauseBtn);
    connect(m_view, &view::MainWidget::clearButtonClicked, this, &Controller::onClearBtn);

    // Init view state
    m_view->setPausedButtonsState();
    m_view->show();

    // Init model state
    m_model->setIsStarted(false);
}


void Controller::setReceiver(utils::recv::DataReceiver *receiver)
{
    if (m_receiver != nullptr) {
        disconnect(m_receiver, &utils::recv::DataReceiver::readyRead, this, &Controller::onDetectorReadyRead);
    }
    m_receiver = receiver;
    connect(m_receiver, &utils::recv::DataReceiver::readyRead, this, &Controller::onDetectorReadyRead);
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

void Controller::onDetectorReadyRead()
{
    m_model->receiveNewSpectrumData(m_receiver->recvData().second);
}

}
}

