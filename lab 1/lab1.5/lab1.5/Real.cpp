#include "Real.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

Number Real::getNumber() const
{
    return number;
}

void Real::setNumber(const Number& number)
{
    this->number = number;
}

void Real::Init(const Number& number)
{
    setNumber(number);
}

void Real::Read()
{
    Number temp;

    std::cout << "Enter real number:" << std::endl;
    temp.Read();

    Init(temp);
}

void Real::Display() const
{
    std::cout << "Real number = " << number.getValue() << std::endl;
}

std::string Real::toString() const
{
    std::ostringstream stream;

    stream << std::fixed << std::setprecision(2)
        << number.getValue();

    return stream.str();
}

float Real::power(float exponent) const
{
    float base = number.getValue();

    if (base == 0.0f && exponent < 0.0f)
    {
        throw std::invalid_argument(
            "Zero cannot be raised to a negative power."
        );
    }

    if (base < 0.0f && std::floor(exponent) != exponent)
    {
        throw std::invalid_argument(
            "A negative number cannot be raised to a fractional power."
        );
    }

    float result = std::pow(base, exponent);

    if (!std::isfinite(result))
    {
        throw std::invalid_argument(
            "Power operation produced an invalid result."
        );
    }

    return result;
}

float Real::logarithm() const
{
    float value = number.getValue();

    if (value <= 0.0f)
    {
        throw std::invalid_argument(
            "Logarithm is defined only for positive numbers."
        );
    }

    return std::log(value);
}