#pragma once

#include <QWidget>
#include <QRadioButton>
#include <QListWidget>
#include <QGroupBox>
#include <QMap>
#include "simulatorgraph.h"
#include "sliderwithlabel.h"
#include "simulator.h"

#include <QTimer>
#include <boost/asio.hpp>

using namespace model;
using namespace view;
using namespace sim;

namespace ba = boost::asio;

class SimulatorWidget : public QWidget
{
    Q_OBJECT

public:
    SimulatorWidget(QWidget *parent = nullptr);
    ~SimulatorWidget();

private:
    static const int num_classes = 10;

    SimulatorGraph *m_graph;
    SliderWithLabel *m_slider[num_classes];
    QRadioButton *m_modelSpectrumsRaB;
    QRadioButton *m_realSpectrumsRaB;
    QListWidget *m_realSpectrumsLw;
    QGroupBox *m_slidersGB;
    QGroupBox *m_realGB;
    QMap<QListWidgetItem *, std::string> m_namesMap;

    Simulator *m_simulator;

private slots:
    void onActivityChanged(int id, qreal value);
    void onReadyRead(data_t data);
    void onRadioButtonToggled();
    void onItemClicked(QListWidgetItem *item);

};
