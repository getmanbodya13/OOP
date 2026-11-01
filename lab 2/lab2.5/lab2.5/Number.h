#pragma once
#include <iostream>
#include <string>

using namespace std;

class Number
{
private:
    float value;

public:
    Number();
    Number(float value);
    Number(const Number& n);

    float getValue() const;
    void setValue(float value);

    void Init(float value);
    void Display() const;
    void Read();

    Number add(const Number& n) const;
    Number divide(const Number& n) const;

    Number& operator=(const Number& n);

    friend ostream& operator<<(ostream& out, const Number& n);
    friend istream& operator>>(istream& in, Number& n);

    operator string() const;

    Number& operator++();
    Number operator++(int);

    Number& operator--();
    Number operator--(int);

    ~Number();
};