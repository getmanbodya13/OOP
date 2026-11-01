#include "Real.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

Real::Real()
    : number()
{
}

Real::Real(float value)
    : number(value)
{
}

Real::Real(const Number& n)
    : number(n)
{
}

Real::Real(const Real& r)
    : number(r.number)
{
}

Number Real::getNumber() const
{
    return number;
}

void Real::setNumber(const Number& n)
{
    number = n;
}

void Real::Init(float value)
{
    number.setValue(value);
}

void Real::Display() const
{
    cout << "Real number = " << number.getValue() << endl;
}

void Real::Read()
{
    cout << "Enter real number: ";
    cin >> number;
}

float Real::power(float exponent) const
{
    float result = pow(number.getValue(), exponent);

    if (!isfinite(result))
        throw invalid_argument("Invalid power operation!");

    return result;
}

float Real::logarithm() const
{
    if (number.getValue() <= 0.0f)
        throw invalid_argument("Logarithm is defined only for positive numbers!");

    return log(number.getValue());
}

Real& Real::operator=(const Real& r)
{
    if (this != &r)
        number = r.number;

    return *this;
}

ostream& operator<<(ostream& out, const Real& r)
{
    out << string(r);
    return out;
}

istream& operator>>(istream& in, Real& r)
{
    in >> r.number;
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

Real::~Real()
{
}