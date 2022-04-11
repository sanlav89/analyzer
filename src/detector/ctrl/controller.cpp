#include "controller.h"

namespace detector {
namespace ctrl {

Controller::Controller(view::MainWidget *view, model::Engine *model, QObject *parent)
    : QObject(parent)
    , m_view(view)
    , m_model(model)
{
    connect(m_view, &view::MainWidget::modeChanged, this, &Controller::onModeChanged);
    connect(m_view, &view::MainWidget::activityChanged, this, &Controller::onActivityChanged);
    connect(m_view, &view::MainWidget::nameChanged, this, &Controller::onNameChanged);

    // initial state
    onModeChanged(model::ModeModeling);
    m_view->show();
}

void Controller::onModeChanged(int mode)
{
    m_view->setEnabledWidgets(
                mode == model::ModeModeling,
                mode == model::ModeMeasured
                );
    m_model->changeMode(mode);
    m_view->updateSpectrum(m_model->spectrum());
}

void Controller::onActivityChanged(int id, qreal activity)
{
    m_model->updateActivity(id, activity);
    m_view->updateSpectrum(m_model->spectrum());
}

void Controller::onNameChanged(const std::string &name)
{
    m_model->updateName(name);
    m_view->updateSpectrum(m_model->spectrum());
}

}
}
