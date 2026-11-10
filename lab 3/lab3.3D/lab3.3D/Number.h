#pragma once
#include <string>
#include <iostream>
#include "Object.h"
using namespace std;

class Number : public Object
{
    float value;
public:
    float getValue() const { return value; }
    void setValue(float v);             

    void Init(float v);
    void Read();
    void Display() const;
    string toString() const;

    Number();
    explicit Number(float v);
    Number(const Number& n);

    Number& operator = (const Number& n);

    Number add(const Number& b) const;  
    Number div(const Number& b) const;   

    friend ostream& operator << (ostream& out, const Number& n);
    friend istream& operator >> (istream& in, Number& n);
    operator string () const;

    Number& operator ++ ();            
    Number& operator -- ();
    Number operator ++ (int);
    Number operator -- (int);

    friend Number operator + (const Number& a, const Number& b);
    friend Number operator / (const Number& a, const Number& b);

    ~Number();
};
