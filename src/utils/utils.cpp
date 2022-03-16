#include "utils.h"
#include <sstream>
#include <fstream>

namespace utils {

bool read_features_csv(std::istream &stream, spectrum_t &spectrum, separator_t sep)
{
    std::string line;
    std::getline(stream, line);
    std::stringstream linestream{line};
    std::string cell;

    auto idx = 0;
    while (std::getline(linestream, cell, sep)) {
        if (!cell.empty()) {
            spectrum[idx++] = std::stof(cell);
        }
    }
    return stream.good();
}

spectrum_t readFromSpeFile(const filename_t &filename)
{
    spectrum_t result;
    std::ifstream input(filename, std::ios::in | std::ios::binary);
    char *buffer = reinterpret_cast<char *>(result.data());
    input.read(buffer, sizeof(sample_t) * (SpectrumSize - 1));
    result[SpectrumSize - 1] = 0;
    return result;
}

}

