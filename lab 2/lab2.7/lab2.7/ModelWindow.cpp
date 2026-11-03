#include "ModelWindow.h"
#include <sstream>
#include <stdexcept>

ModelWindow::ModelWindow()
    : title("New Window"),
    x(0), y(0),
    width(400), height(300),
    color("White"),
    visible(true), border(true),
    cursor()
{
}

ModelWindow::ModelWindow(string title, int x, int y,
    int width, int height,
    string color, bool visible,
    bool border, const Cursor& cursor)
    : title("New Window"),
    x(0), y(0),
    width(400), height(300),
    color("White"),
    visible(true), border(true),
    cursor(cursor)
{
    SetTitle(title);
    Resize(width, height);
    SetPosition(x, y);
    SetColor(color);
    SetVisible(visible);
    SetBorder(border);
}

ModelWindow::ModelWindow(const ModelWindow& other)
{
    *this = other;
}

string ModelWindow::GetTitle() const { return title; }
int ModelWindow::GetX() const { return x; }
int ModelWindow::GetY() const { return y; }
int ModelWindow::GetWidth() const { return width; }
int ModelWindow::GetHeight() const { return height; }
string ModelWindow::GetColor() const { return color; }
bool ModelWindow::GetVisible() const { return visible; }
bool ModelWindow::GetBorder() const { return border; }
Cursor ModelWindow::GetCursor() const { return cursor; }

void ModelWindow::SetTitle(const string& value)
{
    if (value.empty())
        throw invalid_argument("Window title cannot be empty!");

    title = value;
}

void ModelWindow::SetX(int value)
{
    SetPosition(value, y);
}

void ModelWindow::SetY(int value)
{
    SetPosition(x, value);
}

void ModelWindow::SetPosition(int newX, int newY)
{
    if (newX < 0 || newY < 0 ||
        newX + width > SCREEN_WIDTH ||
        newY + height > SCREEN_HEIGHT)
        throw invalid_argument("Window exceeds screen boundaries!");

    x = newX;
    y = newY;
}

void ModelWindow::SetWidth(int value)
{
    Resize(value, height);
}

void ModelWindow::SetHeight(int value)
{
    Resize(width, value);
}

void ModelWindow::Resize(int newWidth, int newHeight)
{
    if (newWidth <= 0 || newHeight <= 0 ||
        newWidth > SCREEN_WIDTH ||
        newHeight > SCREEN_HEIGHT ||
        x + newWidth > SCREEN_WIDTH ||
        y + newHeight > SCREEN_HEIGHT)
        throw invalid_argument("Incorrect window size!");

    width = newWidth;
    height = newHeight;
}

void ModelWindow::SetColor(const string& value)
{
    if (value.empty())
        throw invalid_argument("Color cannot be empty!");

    color = value;
}

void ModelWindow::SetVisible(bool value)
{
    visible = value;
}

void ModelWindow::SetBorder(bool value)
{
    border = value;
}

void ModelWindow::SetCursor(const Cursor& value)
{
    cursor = value;
}

void ModelWindow::MoveHorizontal(int dx)
{
    SetPosition(x + dx, y);
}

void ModelWindow::MoveVertical(int dy)
{
    SetPosition(x, y + dy);
}

void ModelWindow::ChangeColor(const string& newColor)
{
    SetColor(newColor);
}

void ModelWindow::Show()
{
    visible = true;
}

void ModelWindow::Hide()
{
    visible = false;
}

void ModelWindow::AddBorder()
{
    border = true;
}

void ModelWindow::RemoveBorder()
{
    border = false;
}

bool ModelWindow::IsVisible() const
{
    return visible;
}

bool ModelWindow::HasBorder() const
{
    return border;
}

void ModelWindow::MoveCursor(int x, int y)
{
    cursor.SetCoordinates(x, y);
}

void ModelWindow::ChangeCursorType(CursorType type)
{
    cursor.SetType(type);
}

void ModelWindow::ChangeCursorSize(int size)
{
    cursor.SetSize(size);
}

void ModelWindow::EraseCursor()
{
    cursor.Erase();
}

void ModelWindow::RestoreCursor()
{
    cursor.Restore();
}
void ModelWindow::Display()
{
    visible = true;
    cursor.Restore();

    cout << *this << endl;
}


string ModelWindow::toString() const
{
    stringstream ss;

    ss << "Window title: " << title << endl;
    ss << "Position: (" << x << ", " << y << ")" << endl;
    ss << "Width: " << width << endl;
    ss << "Height: " << height << endl;
    ss << "Color: " << color << endl;

    ss << "Visible: "
        << (visible ? "Yes" : "No") << endl;

    ss << "Border: "
        << (border ? "Yes" : "No") << endl;

    ss << cursor.toString();

    return ss.str();
}

ModelWindow::operator string() const
{
    return toString();
}

ModelWindow& ModelWindow::operator=(const ModelWindow& other)
{
    if (this != &other)
    {
        title = other.title;
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
        color = other.color;
        visible = other.visible;
        border = other.border;
        cursor = other.cursor;
    }

    return *this;
}

ModelWindow& ModelWindow::operator++()
{
    Resize(width + 1, height);
    return *this;
}

ModelWindow& ModelWindow::operator--()
{
    Resize(width - 1, height);
    return *this;
}

ModelWindow ModelWindow::operator++(int)
{
    ModelWindow temp = *this;
    Resize(width, height + 1);
    return temp;
}

ModelWindow ModelWindow::operator--(int)
{
    ModelWindow temp = *this;
    Resize(width, height - 1);
    return temp;
}

ostream& operator<<(ostream& out, const ModelWindow& w)
{
    out << w.toString();
    return out;
}

istream& operator>>(istream& in, ModelWindow& w)
{
    string title, color;
    int x, y, width, height;
    int visible, border;

    cout << "Enter window title: ";
    getline(in >> ws, title);

    cout << "Enter X: ";
    in >> x;

    cout << "Enter Y: ";
    in >> y;

    cout << "Enter width: ";
    in >> width;

    cout << "Enter height: ";
    in >> height;

    cout << "Enter color: ";
    in >> color;

    cout << "Visible (1 - Yes, 0 - No): ";
    in >> visible;

    cout << "Border (1 - Yes, 0 - No): ";
    in >> border;

    if (!in)
        return in;

    try
    {
        if ((visible != 0 && visible != 1) ||
            (border != 0 && border != 1))
            throw invalid_argument("Incorrect window state!");

        w.SetTitle(title);
        w.SetPosition(x, y);
        w.Resize(width, height);
        w.SetColor(color);
        w.SetVisible(visible == 1);
        w.SetBorder(border == 1);
    }
    catch (const invalid_argument& e)
    {
        in.setstate(ios::failbit);
        cerr << "Input error: " << e.what() << endl;
    }

    return in;
}