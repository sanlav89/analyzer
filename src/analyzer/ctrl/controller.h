#pragma once

#include <QObject>
#include <view/mainwidget.h>
#include <utils/recv/datareceiver.h>
#include <model/analyzer.h>

namespace analyzer {
namespace ctrl {

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(model::Analyzer *model, view::MainWidget *view, QObject *parent = nullptr);

    void setReceiver(utils::recv::DataReceiver *receiver);

private:
    model::Analyzer *m_model;
    view::MainWidget *m_view;
    utils::recv::DataReceiver *m_receiver;

private slots:
    void onStartBtn();
    void onPauseBtn();
    void onClearBtn();
    void onDetectorReadyRead();

};

}
}
