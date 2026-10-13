#pragma once
#include <string>

class ModelWindow
{
public:
    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;

    class Cursor
    {
    public:
        enum class Type
        {
            Horizontal,
            Vertical
        };

        Cursor();

        int GetX() const;
        int GetY() const;
        Type GetType() const;
        int GetSize() const;
        bool IsActive() const;

        bool SetX(int value);
        bool SetY(int value);
        bool SetCoordinates(int x, int y);
        bool SetType(Type value);
        bool SetSize(int value);

        void Erase();
        void Restore();

        bool Init(int x, int y, Type type, int size);
        void Read();
        void Display() const;
        std::string toString() const;

    private:
        int x;
        int y;
        Type type;
        int size;
        bool active;
    };

    ModelWindow();
    ModelWindow(const std::string& title, int x, int y,
        int width, int height, const std::string& color,
        bool visible, bool bordered);

    std::string GetTitle() const;
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    std::string GetColor() const;
    bool IsVisible() const;
    bool HasBorder() const;
    Cursor GetCursor() const;

    bool SetTitle(const std::string& value);
    bool SetX(int value);
    bool SetY(int value);
    bool SetWidth(int value);
    bool SetHeight(int value);
    bool SetColor(const std::string& value);
    void SetVisible(bool value);
    void SetBorder(bool value);
    void SetCursor(const Cursor& value);

    bool MoveHorizontal(int delta);
    bool MoveVertical(int delta);
    bool Resize(int newWidth, int newHeight);
    bool ChangeColor(const std::string& newColor);

    void SetState(bool visible, bool bordered);
    void GetState(bool& visible, bool& bordered) const;

    bool Init(const std::string& title, int x, int y,
        int width, int height, const std::string& color,
        bool visible, bool bordered);

    void Read();
    void Display();
    std::string toString() const;

private:
    std::string title;
    int x;
    int y;
    int width;
    int height;
    std::string color;
    bool visible;
    bool bordered;

    Cursor cursor;

    bool IsValidGeometry(int x, int y,
        int width, int height) const;
};
