#pragma once

#include <QObject>
#include "view/view.h"
#include "dao/detectoraccess.h"
#include "model/analyzer.h"

namespace ctrl {

using namespace view;
using namespace dao;
using namespace model;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Analyzer *model, View *view, QObject *parent = nullptr);

private:
    Analyzer *m_model;
    View *m_view;
    DetectorAccess *m_detector;

private slots:
    void onStartBtn();
    void onPauseBtn();
    void onClearBtn();
    void onDetectorReadyRead(data_t data);

};

}
