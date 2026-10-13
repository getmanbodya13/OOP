#include "ModelWindow.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <utility>

using namespace std;

ModelWindow::Cursor::Cursor()
    : x(1), y(1), type(Type::Horizontal),
    size(1), active(true)
{
}

int ModelWindow::Cursor::GetX() const
{
    return x;
}

int ModelWindow::Cursor::GetY() const
{
    return y;
}

ModelWindow::Cursor::Type ModelWindow::Cursor::GetType() const
{
    return type;
}

int ModelWindow::Cursor::GetSize() const
{
    return size;
}

bool ModelWindow::Cursor::IsActive() const
{
    return active;
}

bool ModelWindow::Cursor::SetX(int value)
{
    if (value < 1 || value > ModelWindow::SCREEN_WIDTH)
        return false;

    x = value;
    return true;
}

bool ModelWindow::Cursor::SetY(int value)
{
    if (value < 1 || value > ModelWindow::SCREEN_HEIGHT)
        return false;

    y = value;
    return true;
}

bool ModelWindow::Cursor::SetCoordinates(int newX, int newY)
{
    if (newX < 1 || newX > ModelWindow::SCREEN_WIDTH ||
        newY < 1 || newY > ModelWindow::SCREEN_HEIGHT)
        return false;

    x = newX;
    y = newY;
    return true;
}

bool ModelWindow::Cursor::SetType(Type value)
{
    if (value != Type::Horizontal &&
        value != Type::Vertical)
        return false;

    type = value;
    return true;
}

bool ModelWindow::Cursor::SetSize(int value)
{
    if (value < 1 || value > 15)
        return false;

    size = value;
    return true;
}

void ModelWindow::Cursor::Erase()
{
    active = false;
}

void ModelWindow::Cursor::Restore()
{
    active = true;
}

bool ModelWindow::Cursor::Init(
    int newX, int newY, Type newType, int newSize)
{
    if (newX < 1 || newX > ModelWindow::SCREEN_WIDTH ||
        newY < 1 || newY > ModelWindow::SCREEN_HEIGHT ||
        (newType != Type::Horizontal &&
            newType != Type::Vertical) ||
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

void ModelWindow::Cursor::Read()
{
    int newX, newY, newSize;
    int typeValue;

    while (true)
    {
        cout << "Cursor X (1-1920): ";
        if (!(cin >> newX))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cout << "Cursor Y (1-1080): ";
        if (!(cin >> newY))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cout << "Cursor type (0 - Horizontal, 1 - Vertical): ";
        if (!(cin >> typeValue))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cout << "Cursor size (1-15): ";
        if (!(cin >> newSize))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        Type newType;
        if (typeValue == 0)
            newType = Type::Horizontal;
        else if (typeValue == 1)
            newType = Type::Vertical;
        else
        {
            cout << "Invalid cursor type!\n";
            continue;
        }

        if (Init(newX, newY, newType, newSize))
            break;

        cout << "Invalid coordinates or size. Try again.\n";
    }
}

void ModelWindow::Cursor::Display() const
{
    cout << toString() << '\n';
}

string ModelWindow::Cursor::toString() const
{
    ostringstream out;

    out << "Cursor: X = " << x
        << ", Y = " << y
        << ", Type = "
        << (type == Type::Horizontal ? "Horizontal" : "Vertical")
        << ", Size = " << size
        << ", State = " << (active ? "Active" : "Erased");

    return out.str();
}

ModelWindow::ModelWindow()
    : title("Untitled"), x(0), y(0),
    width(800), height(600), color("White"),
    visible(true), bordered(true), cursor()
{
}

ModelWindow::ModelWindow(
    const string& newTitle, int newX, int newY,
    int newWidth, int newHeight, const string& newColor,
    bool newVisible, bool newBordered)
    : ModelWindow()
{
    if (!Init(newTitle, newX, newY, newWidth, newHeight,
        newColor, newVisible, newBordered))
    {
        cout << "Invalid window parameters. Default values used.\n";
    }
}

string ModelWindow::GetTitle() const { return title; }
int ModelWindow::GetX() const { return x; }
int ModelWindow::GetY() const { return y; }
int ModelWindow::GetWidth() const { return width; }
int ModelWindow::GetHeight() const { return height; }
string ModelWindow::GetColor() const { return color; }
bool ModelWindow::IsVisible() const { return visible; }
bool ModelWindow::HasBorder() const { return bordered; }

ModelWindow::Cursor ModelWindow::GetCursor() const
{
    return cursor;
}

bool ModelWindow::SetTitle(const string& value)
{
    if (value.empty())
        return false;

    title = value;
    return true;
}

bool ModelWindow::SetX(int value)
{
    if (!IsValidGeometry(value, y, width, height))
        return false;

    x = value;
    return true;
}

bool ModelWindow::SetY(int value)
{
    if (!IsValidGeometry(x, value, width, height))
        return false;

    y = value;
    return true;
}

bool ModelWindow::SetWidth(int value)
{
    if (!IsValidGeometry(x, y, value, height))
        return false;

    width = value;
    return true;
}

bool ModelWindow::SetHeight(int value)
{
    if (!IsValidGeometry(x, y, width, value))
        return false;

    height = value;
    return true;
}

bool ModelWindow::SetColor(const string& value)
{
    if (value.empty())
        return false;

    color = value;
    return true;
}

void ModelWindow::SetVisible(bool value)
{
    visible = value;
}

void ModelWindow::SetBorder(bool value)
{
    bordered = value;
}

void ModelWindow::SetCursor(const Cursor& value)
{
    cursor = value;
}

bool ModelWindow::IsValidGeometry(
    int newX, int newY, int newWidth, int newHeight) const
{
    return newX >= 0 && newY >= 0 &&
        newWidth > 0 && newHeight > 0 &&
        newWidth <= SCREEN_WIDTH &&
        newHeight <= SCREEN_HEIGHT &&
        newX <= SCREEN_WIDTH - newWidth &&
        newY <= SCREEN_HEIGHT - newHeight;
}

bool ModelWindow::MoveHorizontal(int delta)
{
    long long newX = static_cast<long long>(x) + delta;

    if (newX < 0 || newX > SCREEN_WIDTH - width)
        return false;

    x = static_cast<int>(newX);
    return true;
}

bool ModelWindow::MoveVertical(int delta)
{
    long long newY = static_cast<long long>(y) + delta;

    if (newY < 0 || newY > SCREEN_HEIGHT - height)
        return false;

    y = static_cast<int>(newY);
    return true;
}

bool ModelWindow::Resize(int newWidth, int newHeight)
{
    if (!IsValidGeometry(x, y, newWidth, newHeight))
        return false;

    width = newWidth;
    height = newHeight;
    return true;
}

bool ModelWindow::ChangeColor(const string& newColor)
{
    return SetColor(newColor);
}

void ModelWindow::SetState(bool newVisible, bool newBordered)
{
    visible = newVisible;
    bordered = newBordered;
}

void ModelWindow::GetState(
    bool& currentVisible, bool& currentBordered) const
{
    currentVisible = visible;
    currentBordered = bordered;
}

bool ModelWindow::Init(
    const string& newTitle, int newX, int newY,
    int newWidth, int newHeight, const string& newColor,
    bool newVisible, bool newBordered)
{
    if (newTitle.empty() || newColor.empty() ||
        !IsValidGeometry(newX, newY, newWidth, newHeight))
    {
        return false;
    }

    title = newTitle;
    x = newX;
    y = newY;
    width = newWidth;
    height = newHeight;
    color = newColor;
    visible = newVisible;
    bordered = newBordered;

    return true;
}

void ModelWindow::Read()
{
    string newTitle, newColor;
    int newX, newY, newWidth, newHeight;
    int visibleValue, borderValue;

    while (true)
    {
        cout << "\nWindow title: ";
        cin >> ws;
        getline(cin, newTitle);

        cout << "X coordinate: ";
        if (!(cin >> newX))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cout << "Y coordinate: ";
        if (!(cin >> newY))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cout << "Width: ";
        if (!(cin >> newWidth))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cout << "Height: ";
        if (!(cin >> newHeight))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cout << "Color: ";
        cin >> newColor;

        cout << "Visible (1 - Yes, 0 - No): ";
        if (!(cin >> visibleValue) ||
            (visibleValue != 0 && visibleValue != 1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter 0 or 1!\n";
            continue;
        }

        cout << "Border (1 - Yes, 0 - No): ";
        if (!(cin >> borderValue) ||
            (borderValue != 0 && borderValue != 1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter 0 or 1!\n";
            continue;
        }

        if (Init(newTitle, newX, newY, newWidth, newHeight,
            newColor, visibleValue == 1, borderValue == 1))
            break;

        cout << "Invalid window parameters or screen boundaries. Try again.\n";
    }
}

void ModelWindow::Display()
{
    visible = true;
    cout << toString() << '\n';
    cursor.Display();
}

string ModelWindow::toString() const
{
    ostringstream out;

    out << "Window: " << title
        << "\nPosition: (" << x << ", " << y << ')'
        << "\nSize: " << width << " x " << height
        << "\nColor: " << color
        << "\nVisible: " << (visible ? "Yes" : "No")
        << "\nBorder: " << (bordered ? "Yes" : "No");

    return out.str();
}
