#include "Complex.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

Complex::Complex()
{
    x = 0;
    y = 0;
}

Complex::Complex(double real, double imaginary)
{
    x = real;
    y = imaginary;
}

void Complex::Init(double real, double imaginary)
{
    x = real;
    y = imaginary;
}

void Complex::Read()
{
    cout << "Enter the real part: ";
    cin >> x;

    cout << "Enter the imaginary part: ";
    cin >> y;
}

void Complex::Display() const
{
    cout << toString() << endl;
}

string Complex::toString() const
{
    ostringstream out;

    out << fixed << setprecision(2) << x;

    if (y >= 0)
    {
        out << " + " << y << "i";
    }
    else
    {
        out << " - " << -y << "i";
    }

    return out.str();
}

Complex Complex::sub(const Complex& other) const
{
    return Complex(
        x - other.x,
        y - other.y
    );
}

Complex Complex::div(const Complex& other) const
{
    double denominator =
        other.x * other.x +
        other.y * other.y;

    if (denominator == 0)
    {
        throw invalid_argument(
            "Error: division by zero complex number!"
        );
    }

    double realPart =
        (x * other.x + y * other.y) / denominator;

    double imaginaryPart =
        (other.x * y - x * other.y) / denominator;

    return Complex(realPart, imaginaryPart);
}

Complex Complex::conj() const
{
    return Complex(x, -y);
}