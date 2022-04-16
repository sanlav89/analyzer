#include "simulator.h"

namespace sim {

Simulator::Simulator(const double &countRate)
    : m_countRate{countRate}
{
}

void Simulator::setGenerator(const gen::GeneratorPtr &generator)
{
    m_generator = generator;
}

void Simulator::setActivity(size_t id, utils::activity_t activity)
{
    m_generator->updateActivity(id, activity);
}

void Simulator::changeSpectrumName(const utils::name_t &name)
{
    m_generator->updateName(name);
}

utils::spectrum_t Simulator::spectrum() const
{
    return m_generator->spectrum();
}

utils::names_t Simulator::names() const
{
    return m_generator->names();
}

}
