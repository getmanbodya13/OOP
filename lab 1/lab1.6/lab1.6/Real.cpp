#include "Real.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

float Real::Number::getValue() const
{
    return value;
}

void Real::Number::setValue(float value)
{
    if (!std::isfinite(value))
    {
        throw std::invalid_argument("Number must be a finite value.");
    }

    this->value = value;
}

void Real::Number::Init(float value)
{
    setValue(value);
}

void Real::Number::Read()
{
    float value;

    std::cout << "Enter number: ";
    std::cin >> value;

    while (!std::cin || !std::isfinite(value))
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "Invalid value. Enter a finite number: ";
        std::cin >> value;
    }

    Init(value);
}

void Real::Number::Display() const
{
    std::cout << "Number = " << value << std::endl;
}

std::string Real::Number::toString() const
{
    std::ostringstream stream;

    stream << std::fixed << std::setprecision(2) << value;

    return stream.str();
}

Real::Number Real::Number::add(const Number& other) const
{
    Number result;
    result.Init(value + other.value);
    return result;
}

Real::Number Real::Number::divide(const Number& other) const
{
    if (other.value == 0.0f)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    Number result;
    result.Init(value / other.value);
    return result;
}


Real::Number Real::getNumber() const
{
    return number;
}

void Real::setNumber(const Real::Number& number)
{
    this->number = number;
}

void Real::Init(const Real::Number& number)
{
    setNumber(number);
}

void Real::Read()
{
    Real::Number temp;

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