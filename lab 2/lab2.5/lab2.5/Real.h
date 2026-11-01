#pragma once
#include "Number.h"

class Real
{
private:
    Number number;

public:
    Real();
    Real(float value);
    Real(const Number& n);
    Real(const Real& r);

    Number getNumber() const;
    void setNumber(const Number& n);

    void Init(float value);
    void Display() const;
    void Read();

    float power(float exponent) const;
    float logarithm() const;

    Real& operator=(const Real& r);

    friend ostream& operator<<(ostream& out, const Real& r);
    friend istream& operator>>(istream& in, Real& r);

    operator string() const;

    Real& operator++();
    Real operator++(int);

    Real& operator--();
    Real operator--(int);

    ~Real();
};