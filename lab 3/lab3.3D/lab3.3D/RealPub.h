#pragma once
#include "Number.h"

class RealPub : public Number
{
public:
    RealPub();
    explicit RealPub(float v);
    RealPub(const RealPub& r);
    explicit RealPub(const Number& n);

    RealPub pow(float p) const;             
    RealPub log() const;               
    RealPub log(float base) const;          
    RealPub& operator = (const RealPub& r);
    RealPub& operator ++ ();
    RealPub& operator -- ();
    RealPub operator ++ (int);
    RealPub operator -- (int);

    friend RealPub operator + (const RealPub& a, const RealPub& b);
    friend RealPub operator / (const RealPub& a, const RealPub& b);
};