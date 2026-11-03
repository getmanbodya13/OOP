#pragma once
#include <iostream>
#include <string>
#include "Cursor.h"

using namespace std;

class ModelWindow
{
private:
    string title;

    int x;
    int y;

    int width;
    int height;

    string color;

    bool visible;
    bool border;

    Cursor cursor;

    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;

public:
    ModelWindow();

    ModelWindow(string title, int x, int y,
        int width, int height,
        string color, bool visible,
        bool border, const Cursor& cursor);

    ModelWindow(const ModelWindow& other);

    string GetTitle() const;
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    string GetColor() const;
    bool GetVisible() const;
    bool GetBorder() const;
    Cursor GetCursor() const;

    void SetTitle(const string& value);
    void SetX(int value);
    void SetY(int value);
    void SetPosition(int x, int y);
    void SetWidth(int value);
    void SetHeight(int value);
    void SetColor(const string& value);
    void SetVisible(bool value);
    void SetBorder(bool value);
    void SetCursor(const Cursor& value);

    // ???????? ? ??????
    void MoveHorizontal(int dx);
    void MoveVertical(int dy);

    void Resize(int newWidth, int newHeight);
    void ChangeColor(const string& newColor);

    void Show();
    void Hide();

    void AddBorder();
    void RemoveBorder();

    bool IsVisible() const;
    bool HasBorder() const;

    void MoveCursor(int x, int y);
    void ChangeCursorType(CursorType type);
    void ChangeCursorSize(int size);
    void EraseCursor();
    void RestoreCursor();

    void Display();
    string toString() const;

    ModelWindow& operator=(const ModelWindow& other);

    operator string() const;

    ModelWindow& operator++();
    ModelWindow& operator--();

    ModelWindow operator++(int);
    ModelWindow operator--(int);

    friend ostream& operator<<(ostream& out, const ModelWindow& w);
    friend istream& operator>>(istream& in, ModelWindow& w);
};