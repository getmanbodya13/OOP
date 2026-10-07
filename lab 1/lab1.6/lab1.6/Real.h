#pragma once

#include <string>

class Real
{
public:
    class Number
    {
    private:
        float value;

    public:
        float getValue() const;
        void setValue(float value);

        void Init(float value);
        void Read();
        void Display() const;
        std::string toString() const;

        Number add(const Number& other) const;
        Number divide(const Number& other) const;
    };

private:
    Number number;

public:
    // ?????? ??????? ??????????
    Real::Number getNumber() const;
    void setNumber(const Real::Number& number);

    void Init(const Real::Number& number);

    void Read();
    void Display() const;

    std::string toString() const;

    float power(float exponent) const;
    float logarithm() const;
};