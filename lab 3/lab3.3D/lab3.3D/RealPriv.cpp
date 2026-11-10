#include "RealPriv.h"
#include "RealMath.h"

RealPriv::RealPriv() : Number() {}
RealPriv::RealPriv(float v) : Number(v) {}
RealPriv::RealPriv(const RealPriv& r) : Number(r) {}
RealPriv::RealPriv(const Number& n) : Number(n) {}

RealPriv RealPriv::add(const RealPriv& b) const { return RealPriv(Number::add(b)); }
RealPriv RealPriv::div(const RealPriv& b) const { return RealPriv(Number::div(b)); }

RealPriv RealPriv::pow(float p) const
{
    return RealPriv(RealMath::Pow(getValue(), p));
}

RealPriv RealPriv::log() const
{
    return RealPriv(RealMath::Log(getValue()));
}

RealPriv RealPriv::log(float base) const
{
    return RealPriv(RealMath::Log(getValue(), base));
}

RealPriv& RealPriv::operator = (const RealPriv& r)
{
    Number::operator = (r);
    return *this;
}

RealPriv::operator string () const { return Number::toString(); }

RealPriv& RealPriv::operator ++ () { setValue(getValue() + 1); return *this; }
RealPriv& RealPriv::operator -- () { setValue(getValue() - 1); return *this; }
RealPriv RealPriv::operator ++ (int) { RealPriv t(*this); ++(*this); return t; }
RealPriv RealPriv::operator -- (int) { RealPriv t(*this); --(*this); return t; }

RealPriv operator + (const RealPriv& a, const RealPriv& b) { return a.add(b); }
RealPriv operator / (const RealPriv& a, const RealPriv& b) { return a.div(b); }

ostream& operator << (ostream& out, const RealPriv& r)
{
    return out << static_cast<const Number&>(r);  
}

istream& operator >> (istream& in, RealPriv& r)
{
    return in >> static_cast<Number&>(r);
}