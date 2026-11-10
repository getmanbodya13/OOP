#include "Number.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

void Number::setValue(float v)
{
    if (!isfinite(v)) throw invalid_argument("Number: value is not finite");
    value = v;
}

void Number::Init(float v) { setValue(v); }

void Number::Read()
{
    float v = 0;
    cout << "value = ? ";
    cin >> v;
    Init(v);
}

void Number::Display() const { cout << toString() << endl; }

string Number::toString() const
{
    stringstream ss;
    ss << "value = " << value;
    return ss.str();
}

Number::Number() : value(0) {}
Number::Number(float v) : value(0) { setValue(v); }
Number::Number(const Number& n) : Object(n), value(n.value) {}

Number& Number::operator = (const Number& n)
{
    value = n.value;
    return *this;
}

Number Number::add(const Number& b) const
{
    return Number(value + b.value);
}

Number Number::div(const Number& b) const
{
    if (b.value == 0) throw domain_error("Number: division by zero");
    return Number(value / b.value);
}

ostream& operator << (ostream& out, const Number& n)
{
    return out << string(n);
}

istream& operator >> (istream& in, Number& n)
{
    float v = 0;
    cout << "value = ? ";
    in >> v;
    n.setValue(v);
    return in;
}

Number::operator string () const { return toString(); }

Number& Number::operator ++ () { setValue(value + 1); return *this; }
Number& Number::operator -- () { setValue(value - 1); return *this; }
Number Number::operator ++ (int) { Number t(*this); ++(*this); return t; }
Number Number::operator -- (int) { Number t(*this); --(*this); return t; }

Number operator + (const Number& a, const Number& b) { return a.add(b); }
Number operator / (const Number& a, const Number& b) { return a.div(b); }

Number::~Number() {}