#include "ComplexPriv.h"
#include <stdexcept>

ComplexPriv::ComplexPriv() : Complex() {}
ComplexPriv::ComplexPriv(double x) : Complex(x) {}
ComplexPriv::ComplexPriv(double x, double y) : Complex(x, y) {}
ComplexPriv::ComplexPriv(const ComplexPriv& c) : Complex(c) {}

ComplexPriv ComplexPriv::sub(const ComplexPriv& b) const
{
    return ComplexPriv(getX() - b.getX(), getY() - b.getY());
}

ComplexPriv ComplexPriv::div(const ComplexPriv& b) const
{
    double d = b.getX() * b.getX() + b.getY() * b.getY();
    if (d == 0) throw invalid_argument("Complex: division by zero");
    return ComplexPriv((getX() * b.getX() + getY() * b.getY()) / d,
        (b.getX() * getY() - getX() * b.getY()) / d);
}

ComplexPriv ComplexPriv::conj() const { return ComplexPriv(getX(), -getY()); }

ComplexPriv& ComplexPriv::operator = (const ComplexPriv& c)
{
    Complex::operator = (c);
    return *this;
}
ComplexPriv::operator string() const { return Complex::toString(); }

ComplexPriv& ComplexPriv::operator ++ () { setX(getX() + 1); return *this; }
ComplexPriv& ComplexPriv::operator -- () { setX(getX() - 1); return *this; }
ComplexPriv ComplexPriv::operator ++ (int) { ComplexPriv t(*this); ++(*this); return t; }
ComplexPriv ComplexPriv::operator -- (int) { ComplexPriv t(*this); --(*this); return t; }
ComplexPriv ComplexPriv::operator ~ () const { return conj(); }

ComplexPriv operator - (const ComplexPriv& a, const ComplexPriv& b) { return a.sub(b); }
ComplexPriv operator / (const ComplexPriv& a, const ComplexPriv& b) { return a.div(b); }

ostream& operator << (ostream& out, const ComplexPriv& c)
{
    return out << static_cast<const Complex&>(c);
}
istream& operator >> (istream& in, ComplexPriv& c)
{
    return in >> static_cast<Complex&>(c);
}