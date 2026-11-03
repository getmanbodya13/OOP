#include "Cursor.h"
#include <stdexcept>
#include <sstream>

Cursor::Cursor()
    : x(1), y(1), type(CursorType::Horizontal),
    size(1), active(true)
{
}

Cursor::Cursor(int x, int y, CursorType type, int size)
    : x(1), y(1), type(CursorType::Horizontal),
    size(1), active(true)
{
    SetCoordinates(x, y);
    SetType(type);
    SetSize(size);
}

Cursor::Cursor(const Cursor& other)
{
    *this = other;
}


int Cursor::GetX() const
{
    return x;
}

int Cursor::GetY() const
{
    return y;
}

CursorType Cursor::GetType() const
{
    return type;
}

int Cursor::GetSize() const
{
    return size;
}

bool Cursor::IsActive() const
{
    return active;
}

void Cursor::SetX(int value)
{
    if (value < 1 || value > 1920)
        throw invalid_argument("Incorrect cursor X coordinate!");

    x = value;
}

void Cursor::SetY(int value)
{
    if (value < 1 || value > 1080)
        throw invalid_argument("Incorrect cursor Y coordinate!");

    y = value;
}

void Cursor::SetCoordinates(int x, int y)
{
    if (x < 1 || x > 1920 || y < 1 || y > 1080)
        throw invalid_argument("Incorrect cursor coordinates!");

    this->x = x;
    this->y = y;
}

void Cursor::SetType(CursorType value)
{
    if (value != CursorType::Horizontal &&
        value != CursorType::Vertical)
        throw invalid_argument("Incorrect cursor type!");

    type = value;
}

void Cursor::SetSize(int value)
{
    if (value < 1 || value > 15)
        throw invalid_argument("Cursor size must be from 1 to 15!");

    size = value;
}


void Cursor::Erase()
{
    active = false;
}


void Cursor::Restore()
{
    active = true;
}


string Cursor::toString() const
{
    stringstream ss;

    ss << "Cursor coordinates: (" << x << ", " << y << ")\n";

    ss << "Cursor type: "
        << (type == CursorType::Horizontal
            ? "Horizontal" : "Vertical") << "\n";

    ss << "Cursor size: " << size << "\n";

    ss << "Cursor state: "
        << (active ? "Active" : "Erased");

    return ss.str();
}

Cursor::operator string() const
{
    return toString();
}

Cursor& Cursor::operator=(const Cursor& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        type = other.type;
        size = other.size;
        active = other.active;
    }

    return *this;
}


ostream& operator<<(ostream& out, const Cursor& c)
{
    out << c.toString();
    return out;
}

istream& operator>>(istream& in, Cursor& c)
{
    int x, y, size;
    int type;

    cout << "Enter cursor X: ";
    in >> x;

    cout << "Enter cursor Y: ";
    in >> y;

    cout << "Enter cursor type (0 - Horizontal, 1 - Vertical): ";
    in >> type;

    cout << "Enter cursor size (1-15): ";
    in >> size;

    if (!in)
        return in;

    try
    {
        if (type != 0 && type != 1)
            throw invalid_argument("Incorrect cursor type!");

        c.SetCoordinates(x, y);
        c.SetType(type == 0
            ? CursorType::Horizontal
            : CursorType::Vertical);
        c.SetSize(size);
    }
    catch (const invalid_argument& e)
    {
        in.setstate(ios::failbit);
        cerr << "Input error: " << e.what() << endl;
    }

    return in;
}