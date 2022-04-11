#pragma once

#include <utils/types.h>

namespace utils {
namespace matlab {

using vector_t = std::vector<double>;

vector_t calcEnergy(const poly_t &poly, int channels = SpectrumSize);
double calcFwhm(const double &energy, const poly_t &poly);
double calcEffifiency(const double &energy, const poly_t &poly);
vector_t gaussian(const vector_t &x, const double &x0, const double &sigma, const double &area);
vector_t substrateModel(const vector_t &energies, const double &a, const double &b, const double &c, const double &d);
spectrum_t generatePortion(const spectrum_t &spectrum, const double &countRate);

}
}

