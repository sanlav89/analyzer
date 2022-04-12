#pragma once

#include <simulator/generator.h>

namespace sim {

class Simulator
{
public:
    Simulator(const double &countRate);
    void setGenerator(const sim::gen::GeneratorPtr &generator);
    void setActivity(size_t id, utils::activity_t activity);
    void changeSpectrumName(const utils::name_t &name);
    utils::spectrum_t spectrum() const;
    utils::names_t names() const;

private:
    double m_countRate;
    sim::gen::GeneratorPtr m_generator;

};

using SimulatorPtr = std::unique_ptr<Simulator>;

}
