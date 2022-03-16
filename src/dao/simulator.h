#pragma once

#include "detectoraccess.h"
#include <QTimer>
#include "spectrummeasured.h"
#include "spectrummodeling.h"

namespace dao {

using namespace sim;

class Simulator : public DetectorAccess
{
    Q_OBJECT
public:

    enum Mode {
        Modeling,
        Measured
    };

    explicit Simulator(const path_t &path, const double &countRate, QObject *parent = nullptr);
    void setActivity(size_t id, activity_t activity);
    void setMode(Mode mode);
    void changeSpectrumName(const std::string &name);
    spectrum_t spectrum() const;
    std::vector<std::string> nuclideNames() const;
    std::vector<std::string> spectrumNames() const;
    poly_t energyPoly() const;
    double countRate() const;

private:

    int m_mode;
    double m_countRate;
    QTimer *m_timer;
    std::unique_ptr<SpectrumModeling> m_fromModel;
    std::unique_ptr<SpectrumMeasured> m_fromFiles;
    data_t m_dataToRead;

private slots:
    void onTimeout();

};

}
