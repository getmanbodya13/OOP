#include "RealMath.h"
#include <cmath>
#include <stdexcept>
using namespace std;

float RealMath::Pow(float x, float p)
{
    if (x == 0 && p < 0)
        throw domain_error("Real: zero cannot be raised to a negative power");
    if (x < 0 && p != std::floor(p))
        throw domain_error("Real: negative base with non-integer exponent");
    float r = std::pow(x, p);
    if (!std::isfinite(r))
        throw overflow_error("Real: result is out of range");
    return r;
}

float RealMath::Log(float x)
{
    if (x <= 0)
        throw domain_error("Real: logarithm of a non-positive number");
    return std::log(x);
}

float RealMath::Log(float x, float base)
{
    if (base <= 0 || base == 1)
        throw domain_error("Real: invalid logarithm base");
    return Log(x) / std::log(base);
}