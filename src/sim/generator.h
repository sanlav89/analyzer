#pragma once

#include <utils/types.h>

namespace sim {

namespace spectrum {

class Generator;
using GeneratorPtr = std::shared_ptr<Generator>;

class Generator
{
public:
    virtual void updateActivity(size_t, utils::activity_t) = 0;
    virtual void updateName(const utils::name_t &) = 0;
    virtual utils::spectrum_t spectrum() const = 0;
    virtual utils::poly_t energyPoly() const = 0;
    virtual utils::names_t names() const = 0;

};

}

}

