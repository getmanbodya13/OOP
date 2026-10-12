#include "ModelWindow.h"
#include <iostream>
#include <sstream>

using namespace std;

ModelWindow::ModelWindow()
    : title("Untitled"),
    x(0), y(0),
    width(400), height(300),
    color("White"),
    visible(false), framed(true)
{
}

string ModelWindow::GetTitle() const { return title; }
int ModelWindow::GetX() const { return x; }
int ModelWindow::GetY() const { return y; }
int ModelWindow::GetWidth() const { return width; }
int ModelWindow::GetHeight() const { return height; }
string ModelWindow::GetColor() const { return color; }
bool ModelWindow::IsVisible() const { return visible; }
bool ModelWindow::HasFrame() const { return framed; }

Cursor ModelWindow::GetCursor() const
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
    if (value < 0 || value + width > SCREEN_WIDTH)
        return false;

    x = value;
    return true;
}

bool ModelWindow::SetY(int value)
{
    if (value < 0 || value + height > SCREEN_HEIGHT)
        return false;

    y = value;
    return true;
}

bool ModelWindow::SetWidth(int value)
{
    if (value <= 0 || x + value > SCREEN_WIDTH)
        return false;

    width = value;
    return true;
}

bool ModelWindow::SetHeight(int value)
{
    if (value <= 0 || y + value > SCREEN_HEIGHT)
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

void ModelWindow::SetFramed(bool value)
{
    framed = value;
}

void ModelWindow::SetCursor(const Cursor& value)
{
    cursor.Init(value.GetX(), value.GetY(),
        value.GetType(), value.GetSize());

    if (!value.IsActive())
        cursor.Erase();
}

bool ModelWindow::MoveHorizontal(int delta)
{
    long long newX = static_cast<long long>(x) + delta;

    if (newX < 0 || newX + width > SCREEN_WIDTH)
        return false;

    x = static_cast<int>(newX);
    return true;
}

bool ModelWindow::MoveVertical(int delta)
{
    long long newY = static_cast<long long>(y) + delta;

    if (newY < 0 || newY + height > SCREEN_HEIGHT)
        return false;

    y = static_cast<int>(newY);
    return true;
}

bool ModelWindow::Resize(int newWidth, int newHeight)
{
    if (newWidth <= 0 || newHeight <= 0)
        return false;

    if (x + static_cast<long long>(newWidth) > SCREEN_WIDTH ||
        y + static_cast<long long>(newHeight) > SCREEN_HEIGHT)
        return false;

    width = newWidth;
    height = newHeight;
    return true;
}

bool ModelWindow::Init(const string& newTitle,
    int newX, int newY,
    int newWidth, int newHeight,
    const string& newColor,
    bool newVisible, bool newFramed)
{
    if (newTitle.empty() || newColor.empty() ||
        newX < 0 || newY < 0 ||
        newWidth <= 0 || newHeight <= 0 ||
        static_cast<long long>(newX) + newWidth > SCREEN_WIDTH ||
        static_cast<long long>(newY) + newHeight > SCREEN_HEIGHT)
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
    framed = newFramed;

    return true;
}

void ModelWindow::Read()
{
    string newTitle, newColor;
    int newX, newY, newWidth, newHeight;
    int visibleValue, framedValue;

    while (true)
    {
        cout << "Window title: ";
        getline(cin >> ws, newTitle);

        cout << "X coordinate: ";
        cin >> newX;

        cout << "Y coordinate: ";
        cin >> newY;

        cout << "Width: ";
        cin >> newWidth;

        cout << "Height: ";
        cin >> newHeight;

        cout << "Color: ";
        cin >> newColor;

        cout << "Visible (0 - no, 1 - yes): ";
        cin >> visibleValue;

        cout << "Framed (0 - no, 1 - yes): ";
        cin >> framedValue;

        if (visibleValue >= 0 && visibleValue <= 1 &&
            framedValue >= 0 && framedValue <= 1 &&
            Init(newTitle, newX, newY, newWidth, newHeight,
                newColor, visibleValue == 1,
                framedValue == 1))
        {
            break;
        }

        cout << "\nInvalid parameters or window outside the screen. "
            << "Please try again.\n\n";
    }

    cout << "Enter cursor parameters:\n";
    cursor.Read();
}

void ModelWindow::Display()
{
    visible = true;

    cout << toString() << endl;
    cursor.Display();
}

string ModelWindow::toString() const
{
    ostringstream out;

    out << "Window title: " << title
        << "\nPosition: (" << x << ", " << y << ")"
        << "\nWidth: " << width
        << "\nHeight: " << height
        << "\nColor: " << color
        << "\nVisible: " << (visible ? "Yes" : "No")
        << "\nFrame: " << (framed ? "Yes" : "No");

    return out.str();
}
