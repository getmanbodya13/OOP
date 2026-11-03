#pragma once
#include <iostream>
#include <string>

using namespace std;

class ModelWindow
{
private:
    string title;
    int x, y;
    int width, height;
    string color;
    bool visible;
    bool border;

    static int counter;

public:
    class Cursor
    {
    public:
        enum Type
        {
            Horizontal,
            Vertical
        };

    private:
        int x, y;
        Type type;
        int size;
        bool visible;

        static int counter;

    public:
        Cursor();
        Cursor(int x, int y, Type type, int size);
        Cursor(const Cursor& other);
        ~Cursor();

        int getX() const;
        int getY() const;
        int getSize() const;
        Type getType() const;
        bool isVisible() const;

        void setCoordinates(int x, int y);
        void setType(Type type);
        void setSize(int size);

        void erase();
        void restore();

        Cursor& operator=(const Cursor& other);

        operator string() const;

        Cursor& operator++();
        Cursor operator++(int);

        Cursor& operator--();
        Cursor operator--(int);

        friend ostream& operator<<(ostream& out,
            const Cursor& c);

        friend istream& operator>>(istream& in,
            Cursor& c);

        static int getCounter();
    };

    ModelWindow();
    ModelWindow(string title, int x, int y,
        int width, int height,
        string color, bool visible,
        bool border,
        const Cursor& cursor);

    ModelWindow(const ModelWindow& other);
    ~ModelWindow();

    string getTitle() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    string getColor() const;
    bool isVisible() const;
    bool hasBorder() const;

    Cursor getCursor() const;

    void setTitle(const string& value);
    void setColor(const string& value);
    void setState(bool visible, bool border);

    bool moveHorizontal(int dx);
    bool moveVertical(int dy);

    bool resize(int width, int height);

    void changeColor(const string& color);

    void setVisible(bool value);
    void setBorder(bool value);

    void Display() const;
    string toString() const;

    operator string() const;

    // ?????????????? ????????
    ModelWindow& operator=(const ModelWindow& other);

    ModelWindow& operator++();
    ModelWindow operator++(int);

    ModelWindow& operator--();
    ModelWindow operator--(int);

    friend ostream& operator<<(ostream& out,
        const ModelWindow& w);

    friend istream& operator>>(istream& in,
        ModelWindow& w);

    static int getCounter();

private:
    Cursor cursor;

    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;
};
