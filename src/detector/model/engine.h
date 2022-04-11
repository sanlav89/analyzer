#pragma once

#include <QObject>
#include <QTimer>
#include <utils/utils.h>
#include <utils/nuclidelibrary/nuclidelibrary.h>
#include <simulator/simulator.h>
#include <simulator/modeling.h>
#include <simulator/measured.h>
#include <model/modes.h>
#include <utils/udp/client.h>

namespace detector {
namespace model {

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);

    void changeMode(int mode);
    void updateActivity(size_t id, utils::activity_t activity);
    void updateName(const utils::name_t &);

    utils::spectrum_t spectrum() const;
    utils::poly_t energyPoly() const;
    utils::names_t nuclidesNames() const;
    utils::names_t measuredNames() const;

private:

    utils::nl::NuclideLibraryPtr m_library;
    sim::SimulatorPtr m_simulator;
    sim::gen::ModelingPtr m_modelingGenerator;
    sim::gen::MeasuredPtr m_measuredGenerator;
    QTimer *m_timer;
    utils::udp::ClientPtr m_udpClient;

    const utils::poly_t m_energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
    const utils::poly_t m_fwhmPoly{0.3180643473,1.2086508047,0.0274012077};
    const utils::poly_t m_efficiencyPoly{-19.424696, 20.563331, -7.695772, 0.906304};
    const double m_tlive = 3600;
    const double m_countRate = 100;

private slots:
    void onTimeout();

};

}
}
