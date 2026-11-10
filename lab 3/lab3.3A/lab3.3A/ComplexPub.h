#pragma once
#include "Complex.h"

class ComplexPub : public Complex
{
public:
    ComplexPub();
    ComplexPub(double x);
    ComplexPub(double x, double y);
    ComplexPub(const ComplexPub& c);
    ComplexPub(const Complex& c);

    ComplexPub sub(const ComplexPub& b) const; 
    ComplexPub div(const ComplexPub& b) const;
    ComplexPub conj() const;                    

    ComplexPub& operator = (const ComplexPub& c);
    operator string() const;
    ComplexPub& operator ++ ();  
    ComplexPub& operator -- ();    
    ComplexPub operator ++ (int);
    ComplexPub operator -- (int);
    ComplexPub operator ~ () const; 

    friend ComplexPub operator - (const ComplexPub& a, const ComplexPub& b);
    friend ComplexPub operator / (const ComplexPub& a, const ComplexPub& b);
};