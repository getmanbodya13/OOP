#include "Real.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

Real::Real(float value)
    : Number(value)
{
}

Real::Real(const Real& other)
    : Number(other)
{
}

Real::~Real()
{
}

Real Real::power(float exponent) const
{
    if (!isfinite(exponent))
    {
        cerr << "Error: Invalid exponent!" << endl;
        exit(EXIT_FAILURE);
    }

    float result = pow(getValue(), exponent);

    if (!isfinite(result))
    {
        cerr << "Error: Invalid power result!" << endl;
        exit(EXIT_FAILURE);
    }

    return Real(result);
}

Real Real::logarithm() const
{
    if (getValue() <= 0.0f)
    {
        cerr << "Error: Logarithm argument must be positive!" << endl;
        exit(EXIT_FAILURE);
    }

    return Real(log(getValue()));
}

Real Real::logarithm(float base) const
{
    if (getValue() <= 0.0f)
    {
        cerr << "Error: Logarithm argument must be positive!" << endl;
        exit(EXIT_FAILURE);
    }

    if (!isfinite(base) || base <= 0.0f || base == 1.0f)
    {
        cerr << "Error: Invalid logarithm base!" << endl;
        exit(EXIT_FAILURE);
    }

    return Real(log(getValue()) / log(base));
}

string Real::toString() const
{
    stringstream ss;
    ss << "Real number: " << getValue();

    return ss.str();
}
