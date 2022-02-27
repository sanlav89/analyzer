#pragma once

#include "types.h"

namespace idf {

class IIdentifier
{
public:
    virtual probas_t identify(const spectrum_t &spectrum) = 0;
};

class Identifier : public IIdentifier
{
public:
    Identifier() = default;

    virtual ~Identifier() = default;

    virtual probas_t identify(const spectrum_t &)
    {
        return probas_t{0.1, 0.2, 0.8, 0.0};
    }
};

using IdentifierPtr = std::unique_ptr<Identifier>;

}

