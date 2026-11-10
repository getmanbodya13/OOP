#pragma once
#include "Number.h"

class Real : public Number
{
public:
    Real(float value = 0.0f);
    Real(const Real& other);
    ~Real() override;

    Real power(float exponent) const;

    Real logarithm() const;
    Real logarithm(float base) const;

    std::string toString() const override;
};
