#pragma once

#include <utils/recv/datareceiver.h>
#include <simulator/simulator.h>
#include <QTimer>

namespace utils {
namespace recv {

class SimulatorReceiver : public DataReceiver
{
    Q_OBJECT
public:
    explicit SimulatorReceiver(QObject *parent = nullptr);

    utils::data_t recvData() const override;

private:
    sim::Simulator *m_simulator;
    utils::data_t m_data;
    QTimer *m_timer;
    qreal m_countRate;

private slots:
    void onTimeout();

};

}
}
