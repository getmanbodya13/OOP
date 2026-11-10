#pragma once
#include <iostream>
#include <string>

class Number
{
private:
    float value;

public:
    Number(float value = 0.0f);
    Number(const Number& other);
    virtual ~Number();

    float getValue() const;
    void setValue(float value);

    Number add(const Number& other) const;
    Number divide(const Number& other) const;

    virtual std::string toString() const;
    operator std::string() const;

    friend std::ostream& operator<<(std::ostream& out, const Number& number);
    friend std::istream& operator>>(std::istream& in, Number& number);
};
