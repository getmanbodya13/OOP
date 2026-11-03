#include <iostream>
#include <string>
#include "ModelWindow.h"
#include <sstream>

using namespace std;

#pragma pack(push, 1)

struct PackedCursorLayout
{
    int x;
    int y;
    CursorType type;
    int size;
    bool active;
};

struct PackedModelWindowLayout
{
    string title;
    int x;
    int y;
    int width;
    int height;
    string color;
    bool visible;
    bool border;
    PackedCursorLayout cursor;
};

#pragma pack(pop)

struct NormalModelWindowLayout
{
    string title;
    int x;
    int y;
    int width;
    int height;
    string color;
    bool visible;
    bool border;
    PackedCursorLayout cursor;
};

int main()
{
    setlocale(LC_ALL, "uk_UA.UTF-8");

    cout << "\n--- CURSOR OBJECTS ---\n";

    Cursor c1;

    Cursor c2(100, 200, CursorType::Horizontal, 5);

    Cursor c3(c2);

    cout << "\nCursor c1:\n" << c1 << endl;
    cout << "\nCursor c2:\n" << c2 << endl;
    cout << "\nCursor c3 (copy):\n" << c3 << endl;

    c1.SetX(50);
    c1.SetY(60);
    c1.SetCoordinates(150, 250);
    c1.SetType(CursorType::Vertical);
    c1.SetSize(10);

    cout << "\nModified cursor:\n" << c1 << endl;

    c1.Erase();
    cout << "\nAfter erasing:\n" << c1 << endl;

    c1.Restore();
    cout << "\nAfter restoring:\n" << c1 << endl;

    c3 = c1;

    cout << "\nAfter assignment:\n" << c3 << endl;

    cout << "\n--- CURSOR INPUT ---\n";

    Cursor inputCursor;

    istringstream cursorInput("70 80 0 4");

    cursorInput >> inputCursor;

    cout << "\nEntered cursor:\n";
    cout << inputCursor << endl;

    cout << "\n======================================";
    cout << "\n--- MODEL WINDOW OBJECTS ---\n";

    ModelWindow w1;

    Cursor windowCursor(300, 400, CursorType::Horizontal, 5);

    ModelWindow w2(
        "Main Window",
        100, 100,
        600, 400,
        "Blue",
        true,
        true,
        windowCursor
    );

    ModelWindow w3(w2);

    cout << "\nDefault window:\n" << w1 << endl;

    cout << "\nInitialized window:\n" << w2 << endl;

    cout << "\nCopied window:\n" << w3 << endl;

    cout << "\n--- GETTERS ---\n";

    cout << "Title: " << w2.GetTitle() << endl;
    cout << "X: " << w2.GetX() << endl;
    cout << "Y: " << w2.GetY() << endl;
    cout << "Width: " << w2.GetWidth() << endl;
    cout << "Height: " << w2.GetHeight() << endl;
    cout << "Color: " << w2.GetColor() << endl;
    cout << "Visible: " << w2.GetVisible() << endl;
    cout << "Border: " << w2.GetBorder() << endl;

    cout << "\nCursor information:\n";
    cout << w2.GetCursor() << endl;

    cout << "\n--- SETTERS ---\n";

    w1.SetTitle("Settings Window");
    w1.SetX(50);
    w1.SetY(50);
    w1.SetWidth(500);
    w1.SetHeight(350);
    w1.SetColor("Green");
    w1.SetVisible(true);
    w1.SetBorder(false);
    w1.SetCursor(c2);

    cout << w1 << endl;

    cout << "\n--- MOVING WINDOW ---\n";

    w2.MoveHorizontal(50);

    cout << "After horizontal movement:\n";
    cout << w2 << endl;

    w2.MoveVertical(30);

    cout << "After vertical movement:\n";
    cout << w2 << endl;

    cout << "\n--- RESIZING WINDOW ---\n";

    w2.Resize(700, 500);

    cout << "After resizing:\n";
    cout << w2 << endl;

    cout << "\n--- COLOR CHANGE ---\n";

    w2.ChangeColor("Red");

    cout << w2 << endl;

    cout << "\n--- VISIBILITY ---\n";

    w2.Hide();

    cout << "Window visible: " << w2.IsVisible() << endl;

    w2.Show();

    cout << "Window visible: " << w2.IsVisible() << endl;

    cout << "\n--- BORDER ---\n";

    w2.RemoveBorder();

    cout << "Has border: " << w2.HasBorder() << endl;

    w2.AddBorder();

    cout << "Has border: " << w2.HasBorder() << endl;

    cout << "\n--- CURSOR OPERATIONS ---\n";

    w2.MoveCursor(500, 600);

    w2.ChangeCursorType(CursorType::Vertical);

    w2.ChangeCursorSize(12);

    cout << w2.GetCursor() << endl;

    w2.EraseCursor();

    cout << "\nErased cursor:\n";
    cout << w2.GetCursor() << endl;

    w2.RestoreCursor();

    cout << "\nRestored cursor:\n";
    cout << w2.GetCursor() << endl;

    cout << "\n--- DISPLAY METHOD ---\n";

    w2.Hide();
    w2.EraseCursor();

    w2.Display();

    cout << "\n--- OPERATOR OVERLOADING ---\n";

    ModelWindow w4(
        "Operator Window",
        100, 100,
        300, 200,
        "White",
        true,
        true,
        c1
    );

    cout << "\nInitial window:\n";
    cout << w4 << endl;

    ModelWindow w5;

    w5 = ++w4;

    cout << "\nAfter w5 = ++w4:\n";
    cout << "w4 width: " << w4.GetWidth() << endl;
    cout << "w5 width: " << w5.GetWidth() << endl;

    w5 = --w4;

    cout << "\nAfter w5 = --w4:\n";
    cout << "w4 width: " << w4.GetWidth() << endl;
    cout << "w5 width: " << w5.GetWidth() << endl;

    w5 = w4++;

    cout << "\nAfter w5 = w4++:\n";
    cout << "w4 height: " << w4.GetHeight() << endl;
    cout << "w5 height: " << w5.GetHeight() << endl;

    w5 = w4--;

    cout << "\nAfter w5 = w4--:\n";
    cout << "w4 height: " << w4.GetHeight() << endl;
    cout << "w5 height: " << w5.GetHeight() << endl;

    cout << "\n--- ASSIGNMENT ---\n";

    w3 = w4;

    cout << w3 << endl;

    cout << "\n--- STRING CONVERSION ---\n";

    string windowString = w2;

    cout << windowString << endl;

    cout << "\n--- INPUT OPERATOR ---\n";

    cout << "\n--- WINDOW INPUT ---\n";

    ModelWindow inputWindow;

    istringstream windowInput(
        "Input Window\n10 20 300 200 Purple 1 0"
    );

    windowInput >> inputWindow;

    if (windowInput)
        cout << "\nEntered window:\n" << inputWindow << endl;

    cout << "\n--- ARRAY OF OBJECTS ---\n";

    ModelWindow windows[3] =
    {
        ModelWindow("Window 1", 0, 0, 300, 200,
                    "Red", true, true, c1),

        ModelWindow("Window 2", 400, 100, 500, 300,
                    "Blue", true, false, c2),

        ModelWindow("Window 3", 1000, 200, 400, 400,
                    "Green", false, true, c3)
    };

    for (int i = 0; i < 3; i++)
    {
        cout << "\nWindow " << i + 1 << ":\n";
        cout << windows[i] << endl;
    }

    cout << "\n--- DYNAMIC OBJECT ---\n";

    ModelWindow* dynamicWindow = new ModelWindow(
        "Dynamic Window",
        200, 200,
        450, 350,
        "Yellow",
        true,
        true,
        c1
    );

    cout << *dynamicWindow << endl;

    delete dynamicWindow;

    cout << "\n--- SCREEN BOUNDARY CHECK ---\n";

    try
    {
        w2.MoveHorizontal(5000);
    }
    catch (const invalid_argument& e)
    {
        cout << "Error caught: " << e.what() << endl;
    }

    try
    {
        w2.Resize(3000, 2000);
    }
    catch (const invalid_argument& e)
    {
        cout << "Error caught: " << e.what() << endl;
    }

    try
    {
        w2.ChangeCursorSize(20);
    }
    catch (const invalid_argument& e)
    {
        cout << "Error caught: " << e.what() << endl;
    }

    cout << "\n--- CLASS SIZE ---\n";

    cout << "ModelWindow sizeof: "
        << sizeof(ModelWindow) << " bytes" << endl;

    cout << "Normal layout sizeof: "
        << sizeof(NormalModelWindowLayout) << " bytes" << endl;

    cout << "Packed layout sizeof (#pragma pack(1)): "
        << sizeof(PackedModelWindowLayout) << " bytes" << endl;

    return 0;
}