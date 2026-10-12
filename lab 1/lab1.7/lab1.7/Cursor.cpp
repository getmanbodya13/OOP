#include "Cursor.h"
#include <iostream>
#include <sstream>

using namespace std;

Cursor::Cursor()
    : x(1), y(1),
    type(CursorType::Horizontal),
    size(1), active(true)
{
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

bool Cursor::SetX(int value)
{
    if (value <= 0)
        return false;

    x = value;
    return true;
}

bool Cursor::SetY(int value)
{
    if (value <= 0)
        return false;

    y = value;
    return true;
}

bool Cursor::SetCoordinates(int newX, int newY)
{
    if (newX <= 0 || newY <= 0)
        return false;

    x = newX;
    y = newY;
    return true;
}

bool Cursor::SetType(CursorType value)
{
    if (value != CursorType::Horizontal &&
        value != CursorType::Vertical)
        return false;

    type = value;
    return true;
}

bool Cursor::SetSize(int value)
{
    if (value < 1 || value > 15)
        return false;

    size = value;
    return true;
}

void Cursor::Erase()
{
    active = false;
}

void Cursor::Restore()
{
    active = true;
}

bool Cursor::Init(int newX, int newY,
    CursorType newType, int newSize)
{
    if (newX <= 0 || newY <= 0 ||
        (newType != CursorType::Horizontal &&
            newType != CursorType::Vertical) ||
        newSize < 1 || newSize > 15)
    {
        return false;
    }

    x = newX;
    y = newY;
    type = newType;
    size = newSize;
    active = true;

    return true;
}

void Cursor::Read()
{
    int newX, newY, newSize, typeValue;

    do
    {
        cout << "Cursor X (> 0): ";
        cin >> newX;

        cout << "Cursor Y (> 0): ";
        cin >> newY;

        cout << "Cursor type (0 - horizontal, 1 - vertical): ";
        cin >> typeValue;

        cout << "Cursor size (1-15): ";
        cin >> newSize;

        if (newX <= 0 || newY <= 0 ||
            (typeValue != 0 && typeValue != 1) ||
            newSize < 1 || newSize > 15)
        {
            cout << "Invalid cursor parameters. Try again.\n\n";
        }
    } while (newX <= 0 || newY <= 0 ||
        (typeValue != 0 && typeValue != 1) ||
        newSize < 1 || newSize > 15);

    Init(newX, newY,
        typeValue == 0 ? CursorType::Horizontal
        : CursorType::Vertical,
        newSize);
}

void Cursor::Display() const
{
    cout << toString() << endl;
}

string Cursor::toString() const
{
    ostringstream out;

    out << "Cursor: X = " << x
        << ", Y = " << y
        << ", type = "
        << (type == CursorType::Horizontal
            ? "horizontal" : "vertical")
        << ", size = " << size
        << ", state = "
        << (active ? "active" : "erased");

    return out.str();
}
