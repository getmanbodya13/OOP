#include "Number.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

float Number::getValue() const
{
    return value;
}

void Number::setValue(float value)
{
    if (!std::isfinite(value))
    {
        throw std::invalid_argument("Number must be a finite value.");
    }

    this->value = value;
}

void Number::Init(float value)
{
    setValue(value);
}

void Number::Read()
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

void Number::Display() const
{
    std::cout << "Number = " << value << std::endl;
}

std::string Number::toString() const
{
    std::ostringstream stream;

    stream << std::fixed << std::setprecision(2) << value;

    return stream.str();
}

Number Number::add(const Number& other) const
{
    Number result;

    result.Init(value + other.value);

    return result;
}

Number Number::divide(const Number& other) const
{
    if (other.value == 0.0f)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    Number result;

    result.Init(value / other.value);

    return result;
}