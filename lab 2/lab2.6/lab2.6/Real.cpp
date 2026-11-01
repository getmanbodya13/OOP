#include "Real.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

int Real::counter = 0;

Real::Real() : number()
{
    counter++;
}

Real::Real(float value) : number(value)
{
    counter++;
}

Real::Real(const Real& other) : number(other.number)
{
    counter++;
}

Real::~Real()
{
    counter--;
}

float Real::getValue() const
{
    return number.getValue();
}

void Real::setValue(float value)
{
    number.setValue(value);
}

float Real::power(float exponent) const
{
    float result = pow(number.getValue(), exponent);

    if (!isfinite(result))
        throw invalid_argument("Invalid power operation");

    return result;
}

float Real::logarithm() const
{
    if (number.getValue() <= 0)
        throw invalid_argument("Logarithm is defined only for positive numbers");

    return log(number.getValue());
}

Real& Real::operator=(const Real& other)
{
    if (this != &other)
    {
        number = other.number;
    }

    return *this;
}

ostream& operator<<(ostream& out, const Real& r)
{
    out << string(r);
    return out;
}

istream& operator>>(istream& in, Real& r)
{
    float value;

    cout << "Enter real number: ";
    in >> value;

    if (in)
    {
        try
        {
            r.setValue(value);
        }
        catch (const invalid_argument&)
        {
            in.setstate(ios::failbit);
        }
    }

    return in;
}

Real::operator string() const
{
    stringstream ss;
    ss << "Real number = " << number.getValue();

    return ss.str();
}

Real& Real::operator++()
{
    ++number;
    return *this;
}

Real Real::operator++(int)
{
    Real temp(*this);
    number++;
    return temp;
}

Real& Real::operator--()
{
    --number;
    return *this;
}

Real Real::operator--(int)
{
    Real temp(*this);
    number--;
    return temp;
}

int Real::getCounter()
{
    return counter;
}

int Real::Number::counter = 0;

Real::Number::Number() : value(0)
{
    counter++;
}

Real::Number::Number(float value) : value(value)
{
    if (!isfinite(value))
        throw invalid_argument("Number must be finite");

    counter++;
}

Real::Number::Number(const Number& other)
    : value(other.value)
{
    counter++;
}

Real::Number::~Number()
{
    counter--;
}

float Real::Number::getValue() const
{
    return value;
}

void Real::Number::setValue(float value)
{
    if (!isfinite(value))
        throw invalid_argument("Number must be finite");

    this->value = value;
}

Real::Number Real::Number::add(const Number& other) const
{
    return Number(value + other.value);
}

Real::Number Real::Number::divide(const Number& other) const
{
    if (other.value == 0)
        throw invalid_argument("Division by zero");

    return Number(value / other.value);
}

Real::Number& Real::Number::operator=(const Number& other)
{
    if (this != &other)
    {
        value = other.value;
    }

    return *this;
}

ostream& operator<<(ostream& out, const Real::Number& n)
{
    out << string(n);
    return out;
}

istream& operator>>(istream& in, Real::Number& n)
{
    float value;

    cout << "Enter number: ";
    in >> value;

    if (in)
    {
        try
        {
            n.setValue(value);
        }
        catch (const invalid_argument&)
        {
            in.setstate(ios::failbit);
        }
    }

    return in;
}

Real::Number::operator string() const
{
    stringstream ss;
    ss << value;

    return ss.str();
}

Real::Number operator+(const Real::Number& a,
    const Real::Number& b)
{
    return Real::Number(a.value + b.value);
}

Real::Number operator/(const Real::Number& a,
    const Real::Number& b)
{
    if (b.value == 0)
        throw invalid_argument("Division by zero");

    return Real::Number(a.value / b.value);
}

Real::Number& Real::Number::operator++()
{
    value++;
    return *this;
}

Real::Number Real::Number::operator++(int)
{
    Number temp(*this);
    value++;
    return temp;
}

Real::Number& Real::Number::operator--()
{
    value--;
    return *this;
}

Real::Number Real::Number::operator--(int)
{
    Number temp(*this);
    value--;
    return temp;
}

int Real::Number::getCounter()
{
    return counter;
}
