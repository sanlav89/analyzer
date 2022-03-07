#pragma once

#include "detector.h"

namespace dao {

using filename_t  = std::string;
using filelist_t = std::vector<filename_t>;

class Simulator : public Detector
{
public:
    Simulator(const filelist_t &filelist);

    void connect() override;
    data_t read() override;
    void disconnect() override;

private:

    filelist_t m_filelist;
    std::vector<spectrum_t> m_spectrums;

    spectrum_t readFromBinaryFile(const filename_t &filename);

};

}
