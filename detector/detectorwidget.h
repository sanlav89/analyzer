#pragma once

#include <QWidget>

#include "nuclidelibrary.h"
#include "detectorgraph.h"
#include "types.h"
#include "sliderwithlabel.h"

#include <QTimer>
//#include <boost/asio.hpp>

using namespace model;
using namespace view;

//namespace ba = boost::asio;

class DetectorWidget : public QWidget
{
    Q_OBJECT

public:
    DetectorWidget(QWidget *parent = nullptr);
    ~DetectorWidget();

private:
    static const int num_classes = 10;

    NuclideLibrary m_library{"nuclidelibrary.json"};
    DetectorGraph *m_graph;
    SliderWithLabel *m_slider[num_classes];
    QTimer *m_timer;

    spectrum_t m_spectrum;
    std::vector<qreal> m_energies;
    std::vector<qreal> m_activities;
    nuclides_t m_nuclidesAll;

    const poly_t m_energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
    const poly_t m_fwhmPoly{0.3180643473,1.2086508047,0.0274012077};
    const poly_t m_efficiencyPoly{-19.424696, 20.563331, -7.695772, 0.906304};
    const qreal m_tlive = 3600;
    const qreal m_a = 5;
    const qreal m_b = -0.003;
    const qreal m_c = 0.5;
    const qreal m_d = -0.002;
    void recalcSpectrum();

private slots:
    void onActivityChanged(int id, qreal value);
    void onTimeout();

};
