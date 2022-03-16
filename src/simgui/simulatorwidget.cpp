#include "simulatorwidget.h"
#include <QGridLayout>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include "mathutils.h"
#include <QDebug>
#include <fstream>

using namespace mathutils;

SimulatorWidget::SimulatorWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Detector Simulator");

    m_simulator = new Simulator("../detector/measured", 100, this);

    m_graph = new SimulatorGraph(this);
    m_graph->updateEnergyScale(m_simulator->energyPoly());

    m_modelSpectrumsRaB = new QRadioButton("Spectrum Model");
    m_realSpectrumsRaB = new QRadioButton("Real Measurements");
    m_modelSpectrumsRaB->setChecked(true);
    connect(m_modelSpectrumsRaB, &QRadioButton::toggled, this, &SimulatorWidget::onRadioButtonToggled);

    auto nuclideNames = m_simulator->nuclideNames();
    assert(nuclideNames.size() == num_classes);

    m_realSpectrumsLw = new QListWidget(this);
    auto names = m_simulator->spectrumNames();
    for (const auto &name : names) {
        QListWidgetItem *item = new QListWidgetItem(name.c_str(), m_realSpectrumsLw);
        m_realSpectrumsLw->addItem(item);
        m_namesMap[item] = name;
    }
    connect(m_realSpectrumsLw, &QListWidget::itemClicked, this, &SimulatorWidget::onItemClicked);



    m_slidersGB = new QGroupBox(this);
    QGridLayout *slidersLayout = new QGridLayout(m_slidersGB);
    for (auto i = 0; i < num_classes; i++) {
        m_slider[i] = new SliderWithLabel(this);
        slidersLayout->addWidget(new QLabel(nuclideNames[i].c_str(), this), i, 0, 1, 1);
        slidersLayout->addWidget(m_slider[i], i, 1, 1, 4);
        connect(m_slider[i], &SliderWithLabel::valueChanged, this, &SimulatorWidget::onActivityChanged);
    }
    m_slidersGB->setMaximumHeight(400);

    m_realGB = new QGroupBox(this);
    QGridLayout *realLayout = new QGridLayout(m_realGB);
    realLayout->addWidget(m_realSpectrumsLw);
    m_realGB->setEnabled(false);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_graph, 0, 0, 10, 10);
    mainLayout->addWidget(m_modelSpectrumsRaB, 0, 10, 1, 5);
    mainLayout->addWidget(m_slidersGB, 1, 10, 5, 5);
    mainLayout->addWidget(m_realSpectrumsRaB, 6, 10, 1, 5);
    mainLayout->addWidget(m_realGB, 7, 10, 3, 5);
    setLayout(mainLayout);

    connect(m_simulator, &Simulator::readyRead, this, &SimulatorWidget::onReadyRead);

    m_simulator->setMode(Simulator::Modeling);
    m_graph->updateSpectrum(m_simulator->spectrum());

    // Integration tests
//    auto sigma = calcFwhm(500, m_fwhmPoly) / (2*sqrt(2*log(2)));
//    vector_t shape = gaussian(m_energies, 500, sigma, 1);
//    qDebug() << shape;

}

SimulatorWidget::~SimulatorWidget()
{
}

void SimulatorWidget::onActivityChanged(int id, qreal value)
{
    m_simulator->setActivity(id, value);
    m_graph->updateSpectrum(m_simulator->spectrum());
}

void SimulatorWidget::onReadyRead(data_t data)
{
    try {
        ba::io_context io_context;

        ba::ip::tcp::endpoint ep(
            ba::ip::address::from_string(
                "127.0.0.1"
            ),
            9999
        );
        ba::ip::tcp::socket sock(io_context);

        sock.connect(ep);
        ba::write(sock, ba::buffer(&data, sizeof(data_t)));

    } catch(const boost::system::system_error& ex) {
        std::cout << "boost exception! " << ex.what() << std::endl;
    } catch(const std::exception& ex) {
        std::cout << "std::exception! " << ex.what() << std::endl;
    }
}

void SimulatorWidget::onRadioButtonToggled()
{
    if (m_modelSpectrumsRaB->isChecked()) {
        m_slidersGB->setEnabled(true);
        m_realGB->setEnabled(false);
        m_simulator->setMode(Simulator::Modeling);
        m_graph->updateSpectrum(m_simulator->spectrum());
    } else {
        m_slidersGB->setEnabled(false);
        m_realGB->setEnabled(true);
        m_simulator->setMode(Simulator::Measured);
        if (m_realSpectrumsLw->selectedItems().count() == 0 && m_realSpectrumsLw->count() > 0) {
            auto item = m_realSpectrumsLw->item(0);
            item->setSelected(true);
            m_simulator->changeSpectrumName(m_namesMap[item]);
        } else if (m_realSpectrumsLw->selectedItems().count() > 0) {
            auto item = m_realSpectrumsLw->selectedItems().first();
            m_simulator->changeSpectrumName(m_namesMap[item]);
        }
        m_graph->updateSpectrum(m_simulator->spectrum());
    }
}

void SimulatorWidget::onItemClicked(QListWidgetItem *item)
{
    m_simulator->changeSpectrumName(m_namesMap[item]);
    m_graph->updateSpectrum(m_simulator->spectrum());
}

