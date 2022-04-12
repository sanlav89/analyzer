#include "engine.h"

#include <thread>
#include <boost/asio.hpp>
#include <utils/matlab/matlab.h>
#include <chrono>

namespace detector {
namespace model {

const utils::poly_t m_energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
const utils::poly_t m_fwhmPoly{0.3180643473,1.2086508047,0.0274012077};
const utils::poly_t m_efficiencyPoly{-19.424696, 20.563331, -7.695772, 0.906304};
const double m_tlive = 3600;
const double m_countRate = 100;

Engine::Engine(QObject *parent)
    : QObject{parent}
    , m_library{utils::nl::NuclideLibrary::instance("./data/nuclidelibrary.json")}
    , m_simulator{new sim::Simulator(m_countRate)}
    , m_timer{new QTimer(this)}
    , m_udpClient{new utils::udp::Client}
{
    m_modelingGenerator = sim::gen::ModelingPtr{new sim::gen::Modeling(
                              m_library->nuclidesAll(),
                              m_energyPoly,
                              m_fwhmPoly,
                              m_efficiencyPoly,
                              m_tlive
                              )};
    m_measuredGenerator = sim::gen::MeasuredPtr{new sim::gen::Measured(
                              utils::loadFromDirectory("../../data")
                              )};

    connect(m_timer, &QTimer::timeout, this, &Engine::onTimeout);
    m_timer->start(1000);
}

void Engine::changeMode(int mode)
{
    assert(mode == ModeMeasured || mode == ModeModeling);
    if (mode == ModeModeling) {
        m_simulator->setGenerator(m_modelingGenerator);
    } else {
        m_simulator->setGenerator(m_measuredGenerator);
    }
}

void Engine::updateActivity(size_t id, utils::activity_t activity)
{
    m_simulator->setActivity(id, activity);
}

void Engine::updateName(const utils::name_t &name)
{
    m_simulator->changeSpectrumName(name);
}

utils::spectrum_t Engine::spectrum() const
{
    return m_simulator->spectrum();
}

utils::poly_t Engine::energyPoly() const
{
    return m_energyPoly;
}

utils::names_t Engine::nuclidesNames() const
{
    return m_library->nuclideNames();
}

utils::names_t Engine::measuredNames() const
{
    return m_measuredGenerator->names();
}

void Engine::onTimeout()
{
    using namespace std::chrono;

    utils::data_t dataToSend;
    dataToSend.first = duration_cast<utils::timestamp_t>(
                system_clock::now().time_since_epoch()
                );
    std::fill(dataToSend.second.begin(), dataToSend.second.end(), 0);

    auto tmp = utils::matlab::generatePortion(spectrum(), m_countRate);
    for (auto i = 0u; i < dataToSend.second.size(); i++) {
        dataToSend.second[i] += tmp[i];
    }

    try {
        m_udpClient->sendData(dataToSend);
    } catch(const boost::system::system_error& ex) {
        std::cout << "boost exception! " << ex.what() << std::endl;
    } catch(const std::exception& ex) {
        std::cout << "std::exception! " << ex.what() << std::endl;
    }

}

}
}
