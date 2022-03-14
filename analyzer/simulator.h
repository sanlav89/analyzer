#pragma once

#include "detectoraccess.h"
#include <QTimer>

namespace dao {

using filename_t  = std::string;
using filelist_t = std::vector<filename_t>;

class Simulator : public DetectorAccess
{
    Q_OBJECT
public:
    explicit Simulator(const filelist_t &filelist, const double &countRate, QObject *parent = nullptr);
    data_t read() override;

private:

    QTimer *m_timer;
    double m_countRate;
    std::vector<spectrum_t> m_spectrums;
    data_t m_dataToRead;

    spectrum_t readFromBinaryFile(const filename_t &filename);

private slots:
    void onTimeout();

};

}
