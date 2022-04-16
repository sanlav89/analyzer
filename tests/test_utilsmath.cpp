#include <iostream>
#include <numeric>
#include <cmath>
#include <gtest/gtest.h>

#include <utils/matlab/matlab.h>

using namespace utils;

TEST(MatlabUtils, calcEnergy)
{
    const poly_t energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};

    auto energy = matlab::calcEnergy(energyPoly);

    ASSERT_NEAR(energy[99], 244.5553, 1e-4);
}

TEST(MatlabUtils, calcFwhm)
{
    const poly_t energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
    const poly_t fwhmPoly{0.3180643473,1.2086508047,0.0274012077};

    auto energy = matlab::calcEnergy(energyPoly);
    auto fwhm = matlab::calcFwhm(energy[99], fwhmPoly);

    ASSERT_NEAR(fwhm, 25.9204, 1e-4);
}

TEST(MatlabUtils, calcEffifiency)
{
    const poly_t efficiencyPoly{-19.424696, 20.563331, -7.695772, 0.906304};

    auto efficiency = matlab::calcEffifiency(500.0, efficiencyPoly);

    ASSERT_NEAR(efficiency, 0.0068, 1e-4);
}

TEST(MatlabUtils, gaussian)
{
    const poly_t energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};

    auto x = matlab::calcEnergy(energyPoly);
    auto sigma = 20;
    auto x0 = 500;
    auto area = 100;

    auto gaussian = matlab::gaussian(x, x0, sigma, area);

    ASSERT_NEAR(gaussian[180], 0.9004, 1e-1);
}

TEST(MatlabUtils, substrateModel)
{

    auto tlive = 3600.0;
    auto a = 5 * tlive;
    auto b = -0.003;
    auto c = 0.5 * tlive;
    auto d = -0.002;

    const poly_t energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
    auto x = matlab::calcEnergy(energyPoly);

    auto substrate = matlab::substrateModel(x, a, b, c, d);

    ASSERT_NEAR(substrate[0], 23206.4325057918, 1e-5);
    ASSERT_NEAR(substrate[1023], 4.88703463478699, 1e-5);
}

TEST(MatlabUtils, generatePortion)
{
    auto tlive = 3600.0;
    auto a = 5 * tlive;
    auto b = -0.003;
    auto c = 0.5 * tlive;
    auto d = -0.002;

    const poly_t energyPoly{-30.76253,2.686544,0.0007731202,-1.12527E-06,5.746466E-10};
    auto x = matlab::calcEnergy(energyPoly);

    auto substrate = matlab::substrateModel(x, a, b, c, d);
    spectrum_t spectrum;
    for (auto i = 0u; i < spectrum.size(); i++) {
        spectrum[i] = std::round(substrate[i]);
    }

    auto portion = matlab::generatePortion(spectrum, 100);
    auto portionSum = std::accumulate(portion.begin(), portion.end(), 0);

    ASSERT_TRUE(portionSum > 0);
}

