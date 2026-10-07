#pragma once

#include <string>
#include "Number.h"

class Real
{
private:
    Number number;

public:
    Number getNumber() const;
    void setNumber(const Number& number);

    void Init(const Number& number);

    void Read();
    void Display() const;

    std::string toString() const;

    float power(float exponent) const;
    float logarithm() const;
};