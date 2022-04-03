#pragma once

#include <sim/generator.h>

namespace sim {

class Engine
{
public:
    Engine(const double &countRate);

    void setGenerator(const sim::spectrum::GeneratorPtr &generator);
    void setActivity(size_t id, utils::activity_t activity);
    void changeSpectrumName(const utils::name_t &name);
    utils::poly_t energyPoly() const;
    utils::data_t dataToRead() const;

private:

    double m_countRate;
    sim::spectrum::GeneratorPtr m_generator;

};

}


