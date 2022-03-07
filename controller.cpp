#include "controller.h"

namespace ctrl {

Controller::Controller(View *view, QObject *parent)
    : QObject(parent)
    , m_view(view)
{
    connect(m_view, &View::startButtonClicked, this, &Controller::onStartBtn);
    connect(m_view, &View::pauseButtonClicked, this, &Controller::onPauseBtn);
    connect(m_view, &View::clearButtonClicked, this, &Controller::onClearBtn);
    m_view->show();
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

}

}
