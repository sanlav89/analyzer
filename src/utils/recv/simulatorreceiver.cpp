#include "simulatorreceiver.h"
#include <utils/matlab/matlab.h>
#include <utils/utils.h>
#include <simulator/measured.h>

namespace utils {
namespace recv {

SimulatorReceiver::SimulatorReceiver(QObject *parent)
    : DataReceiver{parent}
    , m_countRate{100}
{
    m_simulator = new sim::Simulator{m_countRate};
    m_simulator->setGenerator(
                sim::gen::MeasuredPtr{
                    new sim::gen::Measured(utils::loadFromDirectory("./data"))
                }
                );
    m_simulator->changeSpectrumName("Th228.spe");

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SimulatorReceiver::onTimeout);
    m_timer->start(1000);
}

utils::data_t SimulatorReceiver::recvData() const
{
    return m_data;
}

void SimulatorReceiver::onTimeout()
{
    using namespace std::chrono;

    m_data.first = duration_cast<utils::timestamp_t>(
                system_clock::now().time_since_epoch()
                );
    std::fill(m_data.second.begin(), m_data.second.end(), 0);

    auto tmp = utils::matlab::generatePortion(m_simulator->spectrum(), m_countRate);
    for (auto i = 0u; i < m_data.second.size(); i++) {
        m_data.second[i] += tmp[i];
    }

    emit readyRead();
}

}
}
