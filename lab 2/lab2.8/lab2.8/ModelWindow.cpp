#include "ModelWindow.h"
#include <sstream>
#include <limits>

int ModelWindow::counter = 0;
int ModelWindow::Cursor::counter = 0;

ModelWindow::Cursor::Cursor()
    : x(1), y(1), type(Horizontal), size(1), visible(true)
{
    counter++;
}

ModelWindow::Cursor::Cursor(int x, int y, Type type, int size)
    : x(1), y(1), type(Horizontal), size(1), visible(true)
{
    setCoordinates(x, y);
    setType(type);
    setSize(size);
    counter++;
}

ModelWindow::Cursor::Cursor(const Cursor& other)
    : x(other.x), y(other.y), type(other.type),
    size(other.size), visible(other.visible)
{
    counter++;
}

ModelWindow::Cursor::~Cursor()
{
    counter--;
}

int ModelWindow::Cursor::getX() const
{
    return x;
}

int ModelWindow::Cursor::getY() const
{
    return y;
}

int ModelWindow::Cursor::getSize() const
{
    return size;
}

ModelWindow::Cursor::Type ModelWindow::Cursor::getType() const
{
    return type;
}

bool ModelWindow::Cursor::isVisible() const
{
    return visible;
}

void ModelWindow::Cursor::setCoordinates(int x, int y)
{
    if (x >= 1 && x <= 1920 && y >= 1 && y <= 1080)
    {
        this->x = x;
        this->y = y;
    }
    else
    {
        cout << "Invalid cursor coordinates!" << endl;
    }
}

void ModelWindow::Cursor::setType(Type type)
{
    if (type == Horizontal || type == Vertical)
        this->type = type;
    else
        cout << "Invalid cursor type!" << endl;
}

void ModelWindow::Cursor::setSize(int size)
{
    if (size >= 1 && size <= 15)
        this->size = size;
    else
        cout << "Cursor size must be from 1 to 15!" << endl;
}

void ModelWindow::Cursor::erase()
{
    visible = false;
}

void ModelWindow::Cursor::restore()
{
    visible = true;
}

ModelWindow::Cursor&
ModelWindow::Cursor::operator=(const Cursor& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        type = other.type;
        size = other.size;
        visible = other.visible;
    }

    return *this;
}

ModelWindow::Cursor::operator string() const
{
    stringstream ss;

    ss << "Cursor: X = " << x
        << ", Y = " << y
        << ", Type = "
        << (type == Horizontal ? "Horizontal" : "Vertical")
        << ", Size = " << size
        << ", Visible = " << (visible ? "Yes" : "No");

    return ss.str();
}

ModelWindow::Cursor&
ModelWindow::Cursor::operator++()
{
    if (size < 15)
        ++size;

    return *this;
}

ModelWindow::Cursor
ModelWindow::Cursor::operator++(int)
{
    Cursor temp(*this);

    ++(*this);

    return temp;
}

ModelWindow::Cursor&
ModelWindow::Cursor::operator--()
{
    if (size > 1)
        --size;

    return *this;
}

ModelWindow::Cursor
ModelWindow::Cursor::operator--(int)
{
    Cursor temp(*this);

    --(*this);

    return temp;
}

ostream& operator<<(ostream& out,
    const ModelWindow::Cursor& c)
{
    out << string(c);
    return out;
}

istream& operator>>(istream& in,
    ModelWindow::Cursor& c)
{
    int x, y, type, size;

    cout << "Cursor X: ";
    in >> x;

    cout << "Cursor Y: ";
    in >> y;

    cout << "Cursor type (0 - Horizontal, 1 - Vertical): ";
    in >> type;

    cout << "Cursor size (1-15): ";
    in >> size;

    if (!in)
        return in;

    if (x < 1 || x > 1920 ||
        y < 1 || y > 1080 ||
        (type != 0 && type != 1) ||
        size < 1 || size > 15)
    {
        in.setstate(ios::failbit);
        return in;
    }

    c.setCoordinates(x, y);
    c.setType(static_cast<ModelWindow::Cursor::Type>(type));
    c.setSize(size);

    return in;
}

int ModelWindow::Cursor::getCounter()
{
    return counter;
}

ModelWindow::ModelWindow()
    : title("New Window"),
    x(0), y(0),
    width(640), height(480),
    color("White"),
    visible(true), border(true),
    cursor()
{
    counter++;
}

ModelWindow::ModelWindow(
    string title, int x, int y,
    int width, int height,
    string color, bool visible,
    bool border, const Cursor& cursor)
    : title("New Window"),
    x(0), y(0),
    width(640), height(480),
    color("White"),
    visible(true), border(true),
    cursor(cursor)
{
    setTitle(title);
    setColor(color);
    setState(visible, border);

    if (x >= 0 && y >= 0 &&
        width > 0 && height > 0 &&
        x + width <= SCREEN_WIDTH &&
        y + height <= SCREEN_HEIGHT)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    counter++;
}

ModelWindow::ModelWindow(const ModelWindow& other)
    : title(other.title),
    x(other.x), y(other.y),
    width(other.width), height(other.height),
    color(other.color),
    visible(other.visible),
    border(other.border),
    cursor(other.cursor)
{
    counter++;
}

ModelWindow::~ModelWindow()
{
    counter--;
}

string ModelWindow::getTitle() const
{
    return title;
}

int ModelWindow::getX() const
{
    return x;
}

int ModelWindow::getY() const
{
    return y;
}

int ModelWindow::getWidth() const
{
    return width;
}

int ModelWindow::getHeight() const
{
    return height;
}

string ModelWindow::getColor() const
{
    return color;
}

bool ModelWindow::isVisible() const
{
    return visible;
}

bool ModelWindow::hasBorder() const
{
    return border;
}

ModelWindow::Cursor ModelWindow::getCursor() const
{
    return cursor;
}

void ModelWindow::setTitle(const string& value)
{
    if (!value.empty())
        title = value;
}

void ModelWindow::setColor(const string& value)
{
    if (!value.empty())
        color = value;
}

void ModelWindow::setState(bool visible, bool border)
{
    this->visible = visible;
    this->border = border;
}

bool ModelWindow::moveHorizontal(int dx)
{
    if (x + dx < 0 ||
        x + dx + width > SCREEN_WIDTH)
    {
        cout << "Horizontal movement is impossible!" << endl;
        return false;
    }

    x += dx;
    return true;
}

bool ModelWindow::moveVertical(int dy)
{
    if (y + dy < 0 ||
        y + dy + height > SCREEN_HEIGHT)
    {
        cout << "Vertical movement is impossible!" << endl;
        return false;
    }

    y += dy;
    return true;
}

bool ModelWindow::resize(int width, int height)
{
    if (width <= 0 || height <= 0 ||
        x + width > SCREEN_WIDTH ||
        y + height > SCREEN_HEIGHT)
    {
        cout << "Invalid window size!" << endl;
        return false;
    }

    this->width = width;
    this->height = height;

    return true;
}

void ModelWindow::changeColor(const string& color)
{
    setColor(color);
}

void ModelWindow::setVisible(bool value)
{
    visible = value;
}

void ModelWindow::setBorder(bool value)
{
    border = value;
}

string ModelWindow::toString() const
{
    stringstream ss;

    ss << "Window title: " << title << endl;
    ss << "Position: (" << x << ", " << y << ")" << endl;
    ss << "Width: " << width << endl;
    ss << "Height: " << height << endl;
    ss << "Color: " << color << endl;
    ss << "Visible: " << (visible ? "Yes" : "No") << endl;
    ss << "Border: " << (border ? "Yes" : "No") << endl;
    ss << cursor;

    return ss.str();
}

ModelWindow::operator string() const
{
    return toString();
}

void ModelWindow::Display() const
{
    cout << *this << endl;
}

ModelWindow&
ModelWindow::operator=(const ModelWindow& other)
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

ModelWindow&
ModelWindow::operator++()
{
    if (x + width < SCREEN_WIDTH &&
        y + height < SCREEN_HEIGHT)
    {
        ++x;
        ++y;
    }

    return *this;
}

ModelWindow ModelWindow::operator++(int)
{
    ModelWindow temp(*this);

    ++(*this);

    return temp;
}

ModelWindow&
ModelWindow::operator--()
{
    if (x > 0 && y > 0)
    {
        --x;
        --y;
    }

    return *this;
}

ModelWindow ModelWindow::operator--(int)
{
    ModelWindow temp(*this);

    --(*this);

    return temp;
}

ostream& operator<<(ostream& out,
    const ModelWindow& w)
{
    out << w.toString();
    return out;
}

istream& operator>>(istream& in,
    ModelWindow& w)
{
    string title, color;
    int x, y, width, height;
    int visible, border;

    cout << "Window title: ";
    getline(in >> ws, title);

    cout << "X: ";
    in >> x;

    cout << "Y: ";
    in >> y;

    cout << "Width: ";
    in >> width;

    cout << "Height: ";
    in >> height;

    cout << "Color: ";
    in >> color;

    cout << "Visible (1 - Yes, 0 - No): ";
    in >> visible;

    cout << "Border (1 - Yes, 0 - No): ";
    in >> border;

    if (!in)
        return in;

    if (title.empty() || color.empty() ||
        x < 0 || y < 0 ||
        width <= 0 || height <= 0 ||
        x + width > ModelWindow::SCREEN_WIDTH ||
        y + height > ModelWindow::SCREEN_HEIGHT ||
        (visible != 0 && visible != 1) ||
        (border != 0 && border != 1))
    {
        in.setstate(ios::failbit);
        return in;
    }

    w.title = title;
    w.x = x;
    w.y = y;
    w.width = width;
    w.height = height;
    w.color = color;
    w.visible = (visible == 1);
    w.border = (border == 1);

    return in;
}

int ModelWindow::getCounter()
{
    return counter;
}
