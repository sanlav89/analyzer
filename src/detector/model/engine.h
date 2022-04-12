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

private slots:
    void onTimeout();

};

}
}
