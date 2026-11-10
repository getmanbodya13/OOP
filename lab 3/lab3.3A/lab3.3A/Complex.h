#pragma once
#include <string>
#include <iostream>
using namespace std;

class Complex
{
    double x, y;
public:
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double x);
    void setY(double y);

    void Init(double x, double y);
    void Read();
    void Display() const;
    string toString() const;

    Complex();
    Complex(double x);
    Complex(double x, double y);
    Complex(const Complex& c);

    friend ostream& operator << (ostream& out, const Complex& c);
    friend istream& operator >> (istream& in, Complex& c);
};