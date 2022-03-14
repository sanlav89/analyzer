#pragma once

#include <QWidget>

#include <QSlider>
#include <QLabel>

#include "nuclidelibrary.h"
#include "types.h"

using namespace model;

class DetectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetectorWidget(QWidget *parent = nullptr);

private:
    static const int num_classes = 10;

    NuclideLibrary m_library;
    DetectorGraph m_graph;
    Server m_server;
    QLabel *m_activityLabels[num_classes];
    QSlider *m_activitySliders[num_classes];
    spectrum_t m_spectrum;

signals:


};
