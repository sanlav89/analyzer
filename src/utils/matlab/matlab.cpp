#include "matlab.h"
#include <cmath>
#include <algorithm>
#include <numeric>

namespace utils {
namespace matlab {

vector_t calcEnergy(const poly_t &poly, int channels)
{
    vector_t result(channels);
    auto x = 0;
    auto sample = [&x, poly] {
        double result = 0;
        x++;
        for (auto i = 0u; i < poly.size(); i++) {
            result += poly[i] * std::pow(x, i);
        }
        return result;
    };
    std::generate(result.begin(), result.end(), sample);
    return result;
}

double calcFwhm(const double &energy, const poly_t &poly)
{
    double result = 0;
    for (auto i = 0u; i < poly.size(); i++) {
        result += poly[i] * std::pow(energy, double(i) * 0.5);
    }
    return result;
}

double calcEffifiency(const double &energy, const poly_t &poly)
{
    double result = 0;
    if (energy > 0) {
        for (auto i = 0u; i < poly.size(); i++) {
            result += poly[i] * std::pow(std::log10(energy), i);
        }
    }
    result = std::pow(10, result);
    return result;
}

vector_t gaussian(const vector_t &x, const double &x0, const double &sigma, const double &area)
{
    vector_t result(x.size());
    double amp = area / (sigma * std::sqrt(2 * M_PI));
    for (auto idx = 0u; idx < x.size(); idx++) {
        result[idx] = amp * std::exp(-std::pow((x[idx] - x0), 2) / (2 * std::pow(sigma, 2)));
    }
    return result;
}

vector_t substrateModel(const vector_t &energies, const double &a, const double &b, const double &c, const double &d)
{
    vector_t result(energies.size());
    for (auto idx = 0u; idx < energies.size(); idx++) {
        result[idx] = a * std::pow(std::exp(b * energies[idx]), 2) + c * std::exp(d * energies[idx]);
    }
    return result;
}

spectrum_t generatePortion(const spectrum_t &spectrum, const double &countRate)
{
    spectrum_t result;
    std::fill(result.begin(), result.end(), 0);

    int countRateRnd = static_cast<double>(std::rand()) / RAND_MAX * countRate + countRate / 2;
    auto score = std::accumulate(spectrum.begin(), spectrum.end(), 0);
    for (auto i = 0; i < countRateRnd; i++) {
        int point = static_cast<double>(std::rand()) / RAND_MAX * score;
        int left = 0;
        for (auto j = 0u; j < spectrum.size(); j++) {
            if (point >= left && point < left + spectrum[j]) {
                result[j] += 1;
                break;
            } else {
                left += spectrum[j];
            }
        }
    }
    return result;
}

}
}

