#pragma once

#include <string>

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