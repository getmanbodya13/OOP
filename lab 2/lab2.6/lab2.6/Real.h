#pragma once

#include <iostream>
#include <string>

using namespace std;

class Real
{
public:

    class Number
    {
    private:
        float value;
        static int counter;

    public:
        Number();
        Number(float value);
        Number(const Number& other);
        ~Number();

        float getValue() const;
        void setValue(float value);

        Number add(const Number& other) const;
        Number divide(const Number& other) const;

        Number& operator=(const Number& other);

        friend ostream& operator<<(ostream& out, const Number& n);
        friend istream& operator>>(istream& in, Number& n);

        operator string() const;

        Number& operator++();
        Number operator++(int);

        Number& operator--();
        Number operator--(int);

        friend Number operator+(const Number& a, const Number& b);
        friend Number operator/(const Number& a, const Number& b);

        static int getCounter();
    };

private:
    Number number;
    static int counter;

public:
    Real();
    Real(float value);
    Real(const Real& other);
    ~Real();

    float getValue() const;
    void setValue(float value);

    float power(float exponent) const;
    float logarithm() const;

    Real& operator=(const Real& other);

    friend ostream& operator<<(ostream& out, const Real& r);
    friend istream& operator>>(istream& in, Real& r);

    operator string() const;

    Real& operator++();
    Real operator++(int);

    Real& operator--();
    Real operator--(int);

    static int getCounter();
};
