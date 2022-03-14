#include "detectorwidget.h"
#include <QGridLayout>
#include "mathutils.h"
#include <QDebug>

using namespace mathutils;

DetectorWidget::DetectorWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Detector Simulator");

    m_graph = new DetectorGraph(this);
    m_graph->updateEnergyScale(m_energyPoly);

    auto nuclideNames = m_library.nuclideNames();
    assert(nuclideNames.size() == num_classes);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_graph, 0, 0, 10, 10);
    for (auto i = 0; i < num_classes; i++) {
        m_slider[i] = new SliderWithLabel(this);
        mainLayout->addWidget(new QLabel(nuclideNames[i].c_str(), this), i, 10, 1, 1);
        mainLayout->addWidget(m_slider[i], i, 11, 1, 4);
        connect(m_slider[i], &SliderWithLabel::valueChanged, this, &DetectorWidget::onActivityChanged);
    }
    setLayout(mainLayout);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &DetectorWidget::onTimeout);
    m_timer->start(1000);

    m_energies = calcEnergy(m_energyPoly);

    m_nuclidesAll = m_library.nuclidesAll();
    m_activities.resize(num_classes);
    std::fill(m_activities.begin(), m_activities.end(), 0);

    recalcSpectrum();
    m_graph->updateSpectrum(m_spectrum);

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
        m_spectrum[idxs] = round(spectrumReal[idxs]);
    }
}

void DetectorWidget::onActivityChanged(int id, qreal value)
{
    m_activities[id] = value;
    recalcSpectrum();
    m_graph->updateSpectrum(m_spectrum);
}

void DetectorWidget::onTimeout()
{
    using namespace std::chrono;
    data_t dataToSend;
    dataToSend.first = duration_cast<timestamp_t>(
                system_clock::now().time_since_epoch()
                );
    dataToSend.second = mathutils::generatePortion(m_spectrum, m_countRate);

    qDebug() << sizeof(data_t);

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

        ba::write(sock, ba::buffer(reinterpret_cast<char *>(&dataToSend), sizeof(data_t)));

        char data[4];
        size_t len = sock.read_some(
            ba::buffer(data)
        );
        std::cout << "receive " << len << "=" << std::string{data, len} << std::endl;
    } catch (const boost::system::system_error& ex) {
        std::cout << "boost exception! " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "std::exception! " << ex.what() << std::endl;
    }
}

