#pragma once

#include <QObject>
#include "view.h"
#include "detector.h"
#include "model.h"

using namespace view;
using namespace dao;
using namespace model;

namespace ctrl {

using ViewPtr = View*;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(ModelPtr model, ViewPtr view, QObject *parent = nullptr);
    void setDetector(DetectorPtr detector);

private:
    ModelPtr m_model;
    ViewPtr m_view;
    DetectorPtr m_detector;

signals:

private slots:
    void onStartBtn();
    void onPauseBtn();
    void onClearBtn();
    void onDetectorReadyRead();

};

}
