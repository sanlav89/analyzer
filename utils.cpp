#include "utils.h"
#include <sstream>


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

}

