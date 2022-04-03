#include "engine.h"
#include <cassert>
#include <utils/mathutils.h>

namespace sim {

Engine::Engine(const double &countRate)
    : m_countRate{countRate}
{
}

void Engine::setGenerator(const spectrum::GeneratorPtr &generator)
{
    m_generator = generator;
}

void Engine::setActivity(size_t id, utils::activity_t activity)
{
    assert(m_generator.ptr() != nullptr);
    m_generator->updateActivity(id, activity);
}

void Engine::changeSpectrumName(const utils::name_t &name)
{
    assert(m_generator.ptr() != nullptr);
    m_generator->updateName(name);
}

utils::poly_t Engine::energyPoly() const
{
    assert(m_generator.ptr() != nullptr);
    return m_generator->energyPoly();
}

utils::data_t Engine::dataToRead() const
{
    using namespace std::chrono;

    utils::data_t result;
    result.first = duration_cast<utils::timestamp_t>(
                system_clock::now().time_since_epoch()
                );
    std::fill(result.second.begin(), result.second.end(), 0);

    auto tmp = utils::math::generatePortion(m_generator->spectrum(), m_countRate);
    for (auto i = 0u; i < result.second.size(); i++) {
        result.second[i] += tmp[i];
    }
    return result;
}

}
