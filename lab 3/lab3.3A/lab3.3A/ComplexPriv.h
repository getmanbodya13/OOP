#pragma once
#include "Complex.h"

class ComplexPriv : private Complex
{
public:
    using Complex::getX;
    using Complex::getY;
    using Complex::setX;
    using Complex::setY;
    using Complex::Init;
    using Complex::Read;
    using Complex::Display;
    using Complex::toString;

    ComplexPriv();
    ComplexPriv(double x);
    ComplexPriv(double x, double y);
    ComplexPriv(const ComplexPriv& c);

    ComplexPriv sub(const ComplexPriv& b) const;
    ComplexPriv div(const ComplexPriv& b) const;
    ComplexPriv conj() const;

    ComplexPriv& operator = (const ComplexPriv& c);
    operator string() const;
    ComplexPriv& operator ++ ();
    ComplexPriv& operator -- ();
    ComplexPriv operator ++ (int);
    ComplexPriv operator -- (int);
    ComplexPriv operator ~ () const;

    friend ComplexPriv operator - (const ComplexPriv& a, const ComplexPriv& b);
    friend ComplexPriv operator / (const ComplexPriv& a, const ComplexPriv& b);

    friend ostream& operator << (ostream& out, const ComplexPriv& c);
    friend istream& operator >> (istream& in, ComplexPriv& c);
};