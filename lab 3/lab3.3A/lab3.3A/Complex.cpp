#include "Complex.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

void Complex::setX(double x)
{
    if (!isfinite(x)) throw invalid_argument("Complex: x is not finite");
    this->x = x;
}
void Complex::setY(double y)
{
    if (!isfinite(y)) throw invalid_argument("Complex: y is not finite");
    this->y = y;
}
void Complex::Init(double x, double y) { setX(x); setY(y); }

void Complex::Read()
{
    double x, y;
    cout << "x = ? "; cin >> x;
    cout << "y = ? "; cin >> y;
    Init(x, y);
}
void Complex::Display() const { cout << toString() << endl; }

string Complex::toString() const
{
    stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}

Complex::Complex() : x(0), y(0) {}
Complex::Complex(double x) : x(0), y(0) { setX(x); }
Complex::Complex(double x, double y) : x(0), y(0) { setX(x); setY(y); }
Complex::Complex(const Complex& c) : x(c.x), y(c.y) {}

ostream& operator << (ostream& out, const Complex& c)
{
    return out << c.toString();
}
istream& operator >> (istream& in, Complex& c)
{
    double x, y;
    cout << "x = ? "; in >> x;
    cout << "y = ? "; in >> y;
    c.Init(x, y);
    return in;
}