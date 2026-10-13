#include "ModelWindow.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    ModelWindow window1;

    cout << "=== Default window ===\n";
    cout << window1.toString() << "\n\n";

    ModelWindow window2(
        "Main Window", 100, 100,
        800, 600, "Blue", true, true
    );

    cout << "=== Parameterized window ===\n";
    cout << window2.toString() << "\n\n";

    ModelWindow window3;

    if (window3.Init(
        "Settings", 50, 50,
        400, 300, "Gray", false, true))
    {
        cout << "Window initialized successfully.\n";
    }

    cout << window3.toString() << "\n\n";

    cout << "=== Moving and resizing ===\n";

    if (window2.MoveHorizontal(50))
        cout << "Horizontal movement successful.\n";
    else
        cout << "Horizontal movement rejected.\n";

    if (window2.MoveVertical(30))
        cout << "Vertical movement successful.\n";

    if (window2.Resize(900, 650))
        cout << "Window resized successfully.\n";

    if (window2.ChangeColor("Green"))
        cout << "Window color changed.\n";

    cout << window2.toString() << "\n\n";

    cout << "=== Boundary check ===\n";

    if (!window2.MoveHorizontal(5000))
        cout << "Movement rejected: screen boundary reached.\n";

    if (!window2.Resize(2000, 1200))
        cout << "Resize rejected: invalid window dimensions.\n";

    cout << "\n";

    window3.SetState(true, false);

    bool isVisible;
    bool hasBorder;

    window3.GetState(isVisible, hasBorder);

    cout << "=== Window state ===\n";
    cout << "Visible: " << (isVisible ? "Yes" : "No") << '\n';
    cout << "Border: " << (hasBorder ? "Yes" : "No") << "\n\n";

    cout << "=== Cursor ===\n";

    ModelWindow::Cursor cursor1;

    cursor1.Init(
        500, 400,
        ModelWindow::Cursor::Type::Horizontal, 5
    );

    cursor1.Display();

    cursor1.SetCoordinates(600, 450);
    cursor1.SetType(ModelWindow::Cursor::Type::Vertical);
    cursor1.SetSize(10);

    cout << "After changing cursor parameters:\n";
    cursor1.Display();

    cursor1.Erase();
    cout << "After erasing:\n";
    cursor1.Display();

    cursor1.Restore();
    cout << "After restoring:\n";
    cursor1.Display();

    window2.SetCursor(cursor1);

    cout << "\n=== Window with cursor ===\n";
    window2.Display();

    cout << "\n=== Array of windows ===\n";

    ModelWindow windows[3] = {
        ModelWindow("Home", 0, 0, 640, 480,
                    "White", true, true),
        ModelWindow("Profile", 650, 0, 600, 400,
                    "Black", true, false),
        ModelWindow("Help", 100, 500, 500, 300,
                    "Yellow", false, true)
    };

    for (int i = 0; i < 3; i++)
    {
        cout << "\nWindow #" << i + 1 << '\n';
        cout << windows[i].toString() << '\n';
    }

    cout << "\n=== Keyboard input ===\n";

    ModelWindow inputWindow;
    inputWindow.Read();

    cout << "\nEntered window:\n";
    cout << inputWindow.toString() << '\n';

    inputWindow.Display();

    return 0;
}
