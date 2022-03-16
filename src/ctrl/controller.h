#pragma once

#include <QObject>
#include "view/view.h"
#include "dao/detectoraccess.h"
#include "model/model.h"

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
    void setDetector(DetectorAccessPtr detector);

private:
    ModelPtr m_model;
    ViewPtr m_view;
    DetectorAccessPtr m_detector;

signals:

private slots:
    void onStartBtn();
    void onPauseBtn();
    void onClearBtn();
    void onDetectorReadyRead(data_t data);

};

}
