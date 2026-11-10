#pragma once
#include "Number.h"

class RealPriv : private Number
{
public:
    using Number::getValue;
    using Number::setValue;
    using Number::Init;
    using Number::Read;
    using Number::Display;
    using Number::toString;
    using Number::Count;

    RealPriv();
    explicit RealPriv(float v);
    RealPriv(const RealPriv& r);
    explicit RealPriv(const Number& n);

    RealPriv add(const RealPriv& b) const;
    RealPriv div(const RealPriv& b) const;
    RealPriv pow(float p) const;
    RealPriv log() const;
    RealPriv log(float base) const;

    RealPriv& operator = (const RealPriv& r);
    operator string () const;
    RealPriv& operator ++ ();
    RealPriv& operator -- ();
    RealPriv operator ++ (int);
    RealPriv operator -- (int);

    friend RealPriv operator + (const RealPriv& a, const RealPriv& b);
    friend RealPriv operator / (const RealPriv& a, const RealPriv& b);

    friend ostream& operator << (ostream& out, const RealPriv& r);
    friend istream& operator >> (istream& in, RealPriv& r);
};