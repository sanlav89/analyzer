#include "utils.h"
#include <sstream>
#include <fstream>
#include <QDir>

namespace utils {

spectrum_t readFromSpeFile(const filename_t &filename)
{
    spectrum_t result;
    std::ifstream input(filename, std::ios::in | std::ios::binary);
    char *buffer = reinterpret_cast<char *>(result.data());
    input.read(buffer, sizeof(sample_t) * (SpectrumSize - 1));
    result[SpectrumSize - 1] = 0;
    return result;
}

std::map<name_t, spectrum_t> loadFromDirectory(const path_t &path)
{
    std::map<name_t, spectrum_t> result;
    QDir directory(path.c_str());
    QStringList spectrumFiles = directory.entryList(QStringList() << "*.spe", QDir::Files);
    for (const auto &entry : spectrumFiles) {
        QString fileName = directory.path() + "/" + entry;
        result[entry.toStdString()] = utils::readFromSpeFile(fileName.toStdString());
    }
    return result;
}

}

