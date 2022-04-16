#pragma once

#include <QObject>
#include <model/engine.h>
#include <view/mainwidget.h>

namespace detector {
namespace ctrl {

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(view::MainWidget *view, model::Engine *model, QObject *parent = nullptr);

private:
    view::MainWidget *m_view;
    model::Engine *m_model;

private slots:
    void onModeChanged(int);
    void onActivityChanged(int, qreal);
    void onNameChanged(const std::string &);

};

}
}
