#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class CursorType
{
    Horizontal,
    Vertical
};

class Cursor
{
private:
    int x;
    int y;
    CursorType type;
    int size;
    bool active;

public:
    Cursor();
    Cursor(int x, int y, CursorType type, int size);
    Cursor(const Cursor& other);

    int GetX() const;
    int GetY() const;
    CursorType GetType() const;
    int GetSize() const;
    bool IsActive() const;

    void SetX(int value);
    void SetY(int value);
    void SetCoordinates(int x, int y);
    void SetType(CursorType value);
    void SetSize(int value);

    void Erase();
    void Restore();

    string toString() const;

    Cursor& operator=(const Cursor& other);
    operator string() const;

    friend ostream& operator<<(ostream& out, const Cursor& c);
    friend istream& operator>>(istream& in, Cursor& c);
};