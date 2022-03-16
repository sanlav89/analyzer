#include "detectorwidget.h"
#include <QGridLayout>
#include <QDir>
#include <QFile>
#include <QDataStream>
#include "mathutils.h"
#include <QDebug>
#include <fstream>

using namespace mathutils;

DetectorWidget::DetectorWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Detector Simulator");

    m_graph = new DetectorGraph(this);
    m_graph->updateEnergyScale(m_energyPoly);

    m_modelSpectrumsRaB = new QRadioButton("Spectrum Model");
    m_realSpectrumsRaB = new QRadioButton("Real Measurements");
    m_modelSpectrumsRaB->setChecked(true);
    connect(m_modelSpectrumsRaB, &QRadioButton::toggled, this, &DetectorWidget::onRadioButtonToggled);
    connect(m_realSpectrumsRaB, &QRadioButton::toggled, this, &DetectorWidget::onRadioButtonToggled);

    m_realSpectrumsLw = new QListWidget(this);
    connect(m_realSpectrumsLw, &QListWidget::itemClicked, this, &DetectorWidget::onItemClicked);

    auto nuclideNames = m_library.nuclideNames();
    assert(nuclideNames.size() == num_classes);

    m_slidersGB = new QGroupBox(this);
    QGridLayout *slidersLayout = new QGridLayout(m_slidersGB);
    for (auto i = 0; i < num_classes; i++) {
        m_slider[i] = new SliderWithLabel(this);
        slidersLayout->addWidget(new QLabel(nuclideNames[i].c_str(), this), i, 0, 1, 1);
        slidersLayout->addWidget(m_slider[i], i, 1, 1, 4);
        connect(m_slider[i], &SliderWithLabel::valueChanged, this, &DetectorWidget::onActivityChanged);
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

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &DetectorWidget::onTimeout);
    m_timer->start(1000);

    m_energies = calcEnergy(m_energyPoly);

    m_nuclidesAll = m_library.nuclidesAll();
    m_activities.resize(num_classes);
    std::fill(m_activities.begin(), m_activities.end(), 0);

    recalcSpectrum();
    m_graph->updateSpectrum(m_currentSpectrum);

    loadMeasurements();
    // Integration tests
//    auto sigma = calcFwhm(500, m_fwhmPoly) / (2*sqrt(2*log(2)));
//    vector_t shape = gaussian(m_energies, 500, sigma, 1);
//    qDebug() << shape;

}

DetectorWidget::~DetectorWidget()
{
}

void DetectorWidget::recalcSpectrum()
{
    std::array<qreal, SpectrumSize> spectrumReal;
    std::fill(spectrumReal.begin(), spectrumReal.end(), 0);

    // activities
    for (auto idxn = 0; idxn < num_classes; idxn++) {
        // gaussians
//        qreal tlive = m_activities[idxn] > 0 ? m_tlive : 0;
        qreal tlive = m_activities[idxn] * m_tlive;
        for (const auto &line : m_nuclidesAll[idxn].lines) {
            qreal eff = calcEffifiency(line.energy, m_efficiencyPoly);
            qreal area = eff * line.intensity * m_activities[idxn] * tlive * 500;
            auto sigma = calcFwhm(line.energy, m_fwhmPoly) / (2*sqrt(2*log(2)));
            vector_t shape = gaussian(m_energies, line.energy, sigma, area);
            for (auto idxs = 0; idxs < SpectrumSize; idxs++) {
                spectrumReal[idxs] += shape[idxs];
            }
        }
        // substrate
        auto substrate = substrateModel(m_energies, m_a * tlive, m_b, m_c * tlive, m_d);
        for (auto idxs = 0; idxs < SpectrumSize; idxs++) {
            spectrumReal[idxs] += substrate[idxs];
        }
    }

    for (auto idxs = 0; idxs < SpectrumSize; idxs++) {
        m_currentSpectrum[idxs] = round(spectrumReal[idxs]);
    }
}

void DetectorWidget::loadMeasurements()
{
    QDir directory("../detector/measured/");
    QStringList spectrumFiles = directory.entryList(QStringList() << "*.spe", QDir::Files);
    for (const auto &entry : spectrumFiles) {
        spectrum_t spectrum;
        QFile f(directory.path() + "/" + entry);
        QDataStream ds(&f);
        if (f.open(QIODevice::ReadOnly)) {
            ds.readRawData(reinterpret_cast<char *>(spectrum.data()), f.size());
            f.close();
            spectrum[SpectrumSize - 1] = 0;
            QListWidgetItem *item = new QListWidgetItem(entry, m_realSpectrumsLw);
            m_realSpectrumsLw->addItem(item);
            m_spectrumsMap[item] = spectrum;
        } else {
            qDebug() << "Error";
        }
    }
}

void DetectorWidget::onActivityChanged(int id, qreal value)
{
    m_activities[id] = value;
    recalcSpectrum();
    m_graph->updateSpectrum(m_currentSpectrum);
}

void DetectorWidget::onTimeout()
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

        using namespace std::chrono;
        m_dataToSend.first = duration_cast<timestamp_t>(
                    system_clock::now().time_since_epoch()
                    );
        m_dataToSend.second = generatePortion(m_currentSpectrum, 100);
        ba::write(sock, ba::buffer(&m_dataToSend, sizeof(data_t)));

    } catch(const boost::system::system_error& ex) {
        std::cout << "boost exception! " << ex.what() << std::endl;
    } catch(const std::exception& ex) {
        std::cout << "std::exception! " << ex.what() << std::endl;
    }
}

void DetectorWidget::onRadioButtonToggled()
{
    if (m_modelSpectrumsRaB->isChecked()) {
        m_slidersGB->setEnabled(true);
        m_realGB->setEnabled(false);
        recalcSpectrum();
        m_graph->updateSpectrum(m_currentSpectrum);
    } else {
        m_slidersGB->setEnabled(false);
        m_realGB->setEnabled(true);
        if (m_realSpectrumsLw->selectedItems().count() == 0 && m_realSpectrumsLw->count() > 0) {
            auto item = m_realSpectrumsLw->item(0);
            item->setSelected(true);
            onItemClicked(item);
        } else if (m_realSpectrumsLw->selectedItems().count() > 0) {
            auto item = m_realSpectrumsLw->selectedItems().first();
            onItemClicked(item);
        }
    }
}

void DetectorWidget::onItemClicked(QListWidgetItem *item)
{
    m_currentSpectrum = m_spectrumsMap[item];
    m_graph->updateSpectrum(m_currentSpectrum);
}

