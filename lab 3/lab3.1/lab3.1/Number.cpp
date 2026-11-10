#include "Number.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

Number::Number(float value)
{
    setValue(value);
}

Number::Number(const Number& other)
{
    setValue(other.value);
}

Number::~Number()
{
}

float Number::getValue() const
{
    return value;
}

void Number::setValue(float value)
{
    if (!isfinite(value))
    {
        cerr << "Error: Invalid number!" << endl;
        exit(EXIT_FAILURE);
    }

    this->value = value;
}

Number Number::add(const Number& other) const
{
    float result = value + other.value;

    if (!isfinite(result))
    {
        cerr << "Error: Addition result is invalid!" << endl;
        exit(EXIT_FAILURE);
    }

    return Number(result);
}

Number Number::divide(const Number& other) const
{
    if (other.value == 0.0f)
    {
        cerr << "Error: Division by zero!" << endl;
        exit(EXIT_FAILURE);
    }

    float result = value / other.value;

    if (!isfinite(result))
    {
        cerr << "Error: Division result is invalid!" << endl;
        exit(EXIT_FAILURE);
    }

    return Number(result);
}

string Number::toString() const
{
    stringstream ss;
    ss << value;
    return ss.str();
}

Number::operator string() const
{
    return toString();
}

ostream& operator<<(ostream& out, const Number& number)
{
    return out << number.toString();
}

istream& operator>>(istream& in, Number& number)
{
    float value;

    cout << "Enter number: ";
    in >> value;

    if (!in || !isfinite(value))
    {
        cerr << "Error: Invalid input!" << endl;
        exit(EXIT_FAILURE);
    }

    number.setValue(value);

    return in;
}
