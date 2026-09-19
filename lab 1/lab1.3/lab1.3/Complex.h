#pragma once

#include <string>

class Complex
{
private:
    double x;
    double y;

public:
    Complex();

    Complex(double real, double imaginary);

    void Init(double real, double imaginary);

    void Read();

    void Display() const;

    std::string toString() const;

    Complex sub(const Complex& other) const;

    Complex div(const Complex& other) const;

    Complex conj() const;
};