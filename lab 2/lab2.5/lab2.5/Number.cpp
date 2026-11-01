#include "Number.h"
#include <sstream>
#include <cmath>
#include <stdexcept>

Number::Number()
{
    value = 0.0f;
}

Number::Number(float value)
{
    setValue(value);
}

Number::Number(const Number& n)
{
    value = n.value;
}

float Number::getValue() const
{
    return value;
}

void Number::setValue(float value)
{
    if (!isfinite(value))
        throw invalid_argument("Number must be finite!");

    this->value = value;
}

void Number::Init(float value)
{
    setValue(value);
}

void Number::Display() const
{
    cout << "Value = " << value << endl;
}

void Number::Read()
{
    float temp;

    cout << "Enter number: ";
    cin >> temp;

    if (cin)
    {
        try
        {
            setValue(temp);
        }
        catch (const invalid_argument& e)
        {
            cerr << e.what() << endl;
        }
    }
}

Number Number::add(const Number& n) const
{
    return Number(value + n.value);
}

Number Number::divide(const Number& n) const
{
    if (n.value == 0.0f)
        throw invalid_argument("Division by zero!");

    return Number(value / n.value);
}

Number& Number::operator=(const Number& n)
{
    if (this != &n)
        value = n.value;

    return *this;
}

ostream& operator<<(ostream& out, const Number& n)
{
    out << string(n);
    return out;
}

istream& operator>>(istream& in, Number& n)
{
    float temp;

    cout << "Enter number: ";
    in >> temp;

    if (in)
    {
        try
        {
            n.setValue(temp);
        }
        catch (const invalid_argument&)
        {
            in.setstate(ios::failbit);
        }
    }

    return in;
}

Number::operator string() const
{
    stringstream ss;

    ss << "Value = " << value;

    return ss.str();
}

Number& Number::operator++()
{
    setValue(value + 1.0f);
    return *this;
}

Number Number::operator++(int)
{
    Number temp(*this);
    setValue(value + 1.0f);
    return temp;
}

Number& Number::operator--()
{
    setValue(value - 1.0f);
    return *this;
}

Number Number::operator--(int)
{
    Number temp(*this);
    setValue(value - 1.0f);
    return temp;
}

Number::~Number()
{
}