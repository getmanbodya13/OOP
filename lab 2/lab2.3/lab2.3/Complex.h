#pragma once
#include <iostream>
#include <string>

class Complex
{
private:
    double x; 
    double y;

public:
    double GetX() const;
    double GetY() const;

    void SetX(double value);
    void SetY(double value);

    Complex();
    Complex(double real, double imaginary);
    Complex(const Complex& other);

    Complex& operator=(const Complex& other);

    void Init(double real, double imaginary);
    void Read();
    void Display() const;
    std::string toString() const;

    operator std::string() const;

    Complex sub(const Complex& other) const;
    Complex div(const Complex& other) const;
    Complex conj() const;

    Complex& operator++();
    Complex& operator--();

    Complex operator++(int);
    Complex operator--(int);

    friend std::ostream& operator<<(std::ostream& out,
        const Complex& value);
    friend std::istream& operator>>(std::istream& in,
        Complex& value);

    friend Complex operator-(const Complex& a, const Complex& b);
    friend Complex operator/(const Complex& a, const Complex& b);
};

#pragma pack(push, 1)
class ComplexPacked
{
private:
    double x;
    double y;
};
#pragma pack(pop)
