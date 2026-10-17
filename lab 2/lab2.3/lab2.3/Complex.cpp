#include "Complex.h"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

double Complex::GetX() const
{
    return x;
}

double Complex::GetY() const
{
    return y;
}

void Complex::SetX(double value)
{
    if (!std::isfinite(value))
        throw std::invalid_argument("Invalid real part.");

    x = value;
}

void Complex::SetY(double value)
{
    if (!std::isfinite(value))
        throw std::invalid_argument("Invalid imaginary part.");

    y = value;
}

Complex::Complex()
    : x(0.0), y(0.0)
{
}

Complex::Complex(double real, double imaginary)
    : x(0.0), y(0.0)
{
    SetX(real);
    SetY(imaginary);
}

Complex::Complex(const Complex& other)
    : x(other.x), y(other.y)
{
}

Complex& Complex::operator=(const Complex& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }

    return *this;
}

void Complex::Init(double real, double imaginary)
{
    SetX(real);
    SetY(imaginary);
}

void Complex::Read()
{
    std::cin >> *this;
}

void Complex::Display() const
{
    std::cout << *this;
}

std::string Complex::toString() const
{
    std::ostringstream out;

    out << std::fixed << std::setprecision(2);
    out << x;

    if (y >= 0)
        out << " + " << y << "i";
    else
        out << " - " << -y << "i";

    return out.str();
}

Complex::operator std::string() const
{
    return toString();
}

Complex Complex::sub(const Complex& other) const
{
    return Complex(x - other.x, y - other.y);
}

Complex Complex::div(const Complex& other) const
{
    double denominator =
        other.x * other.x + other.y * other.y;

    if (denominator == 0.0)
        throw std::domain_error("Division by zero complex number.");

    double real =
        (x * other.x + y * other.y) / denominator;

    double imaginary =
        (other.x * y - x * other.y) / denominator;

    return Complex(real, imaginary);
}

Complex Complex::conj() const
{
    return Complex(x, -y);
}

Complex& Complex::operator++()
{
    SetX(x + 1.0);
    return *this;
}

Complex& Complex::operator--()
{
    SetX(x - 1.0);
    return *this;
}

Complex Complex::operator++(int)
{
    Complex old(*this);
    SetY(y + 1.0);
    return old;
}

Complex Complex::operator--(int)
{
    Complex old(*this);
    SetY(y - 1.0);
    return old;
}

std::ostream& operator<<(std::ostream& out,
    const Complex& value)
{
    out << value.toString();
    return out;
}

std::istream& operator>>(std::istream& in,
    Complex& value)
{
    double real;
    double imaginary;

    std::cout << "Enter real part: ";
    if (!(in >> real))
        return in;

    std::cout << "Enter imaginary part: ";
    if (!(in >> imaginary))
        return in;

    try
    {
        value.SetX(real);
        value.SetY(imaginary);
    }
    catch (const std::invalid_argument&)
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

Complex operator-(const Complex& a, const Complex& b)
{
    return a.sub(b);
}

Complex operator/(const Complex& a, const Complex& b)
{
    return a.div(b);
}
