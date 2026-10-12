#pragma once
#include <string>

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

    int GetX() const;
    int GetY() const;
    CursorType GetType() const;
    int GetSize() const;
    bool IsActive() const;

    bool SetX(int value);
    bool SetY(int value);
    bool SetCoordinates(int newX, int newY);
    bool SetType(CursorType value);
    bool SetSize(int value);

    void Erase();
    void Restore();

    bool Init(int x, int y, CursorType type, int size);
    void Read();
    void Display() const;
    std::string toString() const;
};
