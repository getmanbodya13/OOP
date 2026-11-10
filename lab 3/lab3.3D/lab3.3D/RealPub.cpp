#include "RealPub.h"
#include "RealMath.h"

RealPub::RealPub() : Number() {}
RealPub::RealPub(float v) : Number(v) {}
RealPub::RealPub(const RealPub& r) : Number(r) {}
RealPub::RealPub(const Number& n) : Number(n) {}

RealPub RealPub::pow(float p) const
{
    return RealPub(RealMath::Pow(getValue(), p));
}

RealPub RealPub::log() const
{
    return RealPub(RealMath::Log(getValue()));
}

RealPub RealPub::log(float base) const
{
    return RealPub(RealMath::Log(getValue(), base));
}

RealPub& RealPub::operator = (const RealPub& r)
{
    Number::operator = (r);           
    return *this;
}

RealPub& RealPub::operator ++ () { setValue(getValue() + 1); return *this; }
RealPub& RealPub::operator -- () { setValue(getValue() - 1); return *this; }
RealPub RealPub::operator ++ (int) { RealPub t(*this); ++(*this); return t; }
RealPub RealPub::operator -- (int) { RealPub t(*this); --(*this); return t; }

RealPub operator + (const RealPub& a, const RealPub& b) { return RealPub(a.add(b)); }
RealPub operator / (const RealPub& a, const RealPub& b) { return RealPub(a.div(b)); }