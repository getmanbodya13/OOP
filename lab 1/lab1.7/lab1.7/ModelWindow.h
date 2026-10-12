#pragma once
#include <string>
#include "Cursor.h"

class ModelWindow
{
private:
    std::string title;
    int x;
    int y;
    int width;
    int height;
    std::string color;
    bool visible;
    bool framed;

    Cursor cursor;

    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;

public:
    ModelWindow();

    std::string GetTitle() const;
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    std::string GetColor() const;
    bool IsVisible() const;
    bool HasFrame() const;
    Cursor GetCursor() const;

    bool SetTitle(const std::string& value);
    bool SetX(int value);
    bool SetY(int value);
    bool SetWidth(int value);
    bool SetHeight(int value);
    bool SetColor(const std::string& value);
    void SetVisible(bool value);
    void SetFramed(bool value);
    void SetCursor(const Cursor& value);

    bool MoveHorizontal(int delta);
    bool MoveVertical(int delta);
    bool Resize(int newWidth, int newHeight);

    bool Init(const std::string& title,
        int x, int y, int width, int height,
        const std::string& color,
        bool visible, bool framed);

    void Read();
    void Display();
    std::string toString() const;
};
