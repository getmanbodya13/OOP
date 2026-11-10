#include "ComplexPub.h"
#include <stdexcept>

ComplexPub::ComplexPub() : Complex() {}
ComplexPub::ComplexPub(double x) : Complex(x) {}
ComplexPub::ComplexPub(double x, double y) : Complex(x, y) {}
ComplexPub::ComplexPub(const ComplexPub& c) : Complex(c) {}
ComplexPub::ComplexPub(const Complex& c) : Complex(c) {}

ComplexPub ComplexPub::sub(const ComplexPub& b) const
{
    return ComplexPub(getX() - b.getX(), getY() - b.getY());
}

ComplexPub ComplexPub::div(const ComplexPub& b) const
{
    double d = b.getX() * b.getX() + b.getY() * b.getY();
    if (d == 0) throw invalid_argument("Complex: division by zero");
    return ComplexPub((getX() * b.getX() + getY() * b.getY()) / d,
        (b.getX() * getY() - getX() * b.getY()) / d);
}

ComplexPub ComplexPub::conj() const { return ComplexPub(getX(), -getY()); }

ComplexPub& ComplexPub::operator = (const ComplexPub& c)
{
    Complex::operator = (c);
    return *this;
}
ComplexPub::operator string() const { return toString(); }

ComplexPub& ComplexPub::operator ++ () { setX(getX() + 1); return *this; }
ComplexPub& ComplexPub::operator -- () { setX(getX() - 1); return *this; }
ComplexPub ComplexPub::operator ++ (int) { ComplexPub t(*this); ++(*this); return t; }
ComplexPub ComplexPub::operator -- (int) { ComplexPub t(*this); --(*this); return t; }
ComplexPub ComplexPub::operator ~ () const { return conj(); }

ComplexPub operator - (const ComplexPub& a, const ComplexPub& b) { return a.sub(b); }
ComplexPub operator / (const ComplexPub& a, const ComplexPub& b) { return a.div(b); }