#include "ModelWindow.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    ModelWindow window1;

    cout << "===== WINDOW 1: DEFAULT CONSTRUCTOR =====\n";
    cout << window1.toString() << "\n\n";

    ModelWindow window2;

    if (window2.Init("Main Window", 100, 100,
        600, 400, "Blue", true, true))
    {
        cout << "===== WINDOW 2: INITIALIZED OBJECT =====\n";
        window2.Display();
        cout << endl;
    }

    cout << "\n===== WINDOW OPERATIONS =====\n";

    cout << "Move right by 50: "
        << (window2.MoveHorizontal(50) ? "Success" : "Failed")
        << endl;

    cout << "Move down by 30: "
        << (window2.MoveVertical(30) ? "Success" : "Failed")
        << endl;

    cout << "Resize to 800 x 500: "
        << (window2.Resize(800, 500) ? "Success" : "Failed")
        << endl;

    cout << "Move outside the screen: "
        << (window2.MoveHorizontal(2000) ? "Success" : "Rejected")
        << endl;

    window2.SetColor("Green");
    window2.SetVisible(false);
    window2.SetFramed(false);
    window2.SetTitle("Updated Window");

    cout << "\n===== UPDATED WINDOW =====\n";
    cout << window2.toString() << endl;

    cout << "Visible state: "
        << (window2.IsVisible() ? "Yes" : "No") << endl;

    cout << "Frame state: "
        << (window2.HasFrame() ? "Yes" : "No") << endl;

    cout << "\n===== CURSOR OPERATIONS =====\n";

    Cursor cursor1;
    cursor1.Init(50, 60, CursorType::Horizontal, 5);
    cursor1.Display();

    cursor1.SetCoordinates(70, 80);
    cursor1.SetType(CursorType::Vertical);
    cursor1.SetSize(10);

    cout << "After changing parameters:\n";
    cursor1.Display();

    cursor1.Erase();
    cout << "After erasing:\n";
    cursor1.Display();

    cursor1.Restore();
    cout << "After restoring:\n";
    cursor1.Display();

    window2.SetCursor(cursor1);

    cout << "\n===== WINDOW WITH CURSOR =====\n";
    window2.Display();

    ModelWindow window3;

    cout << "\n===== ENTER WINDOW 3 DATA =====\n";
    window3.Read();

    cout << "\n===== WINDOW 3 =====\n";
    window3.Display();

    cout << "\n===== ARRAY OF WINDOWS =====\n";

    ModelWindow windows[3];

    windows[0].Init("First", 10, 10, 300, 200,
        "Red", true, true);

    windows[1].Init("Second", 400, 100, 500, 300,
        "Yellow", false, true);

    windows[2].Init("Third", 900, 200, 400, 250,
        "Black", true, false);

    for (int i = 0; i < 3; i++)
    {
        cout << "\nWindow " << i + 1 << ":\n";
        cout << windows[i].toString() << endl;
    }

    cout << "\n===== GETTERS AND SETTERS =====\n";

    cout << "Title: " << windows[0].GetTitle() << endl;
    cout << "X: " << windows[0].GetX() << endl;
    cout << "Y: " << windows[0].GetY() << endl;
    cout << "Width: " << windows[0].GetWidth() << endl;
    cout << "Height: " << windows[0].GetHeight() << endl;
    cout << "Color: " << windows[0].GetColor() << endl;

    cout << "Set width to 350: "
        << (windows[0].SetWidth(350) ? "Success" : "Failed")
        << endl;

    cout << "Set height to 250: "
        << (windows[0].SetHeight(250) ? "Success" : "Failed")
        << endl;

    cout << "Set X coordinate to 100: "
        << (windows[0].SetX(100) ? "Success" : "Failed")
        << endl;

    cout << "Set Y coordinate to 100: "
        << (windows[0].SetY(100) ? "Success" : "Failed")
        << endl;

    cout << "Set title: "
        << (windows[0].SetTitle("Final Window")
            ? "Success" : "Failed")
        << endl;

    cout << "\n===== FINAL WINDOW STATE =====\n";
    windows[0].Display();

    cout << "\n===== VALIDATION =====\n";

    cout << "Set cursor size to 20: "
        << (cursor1.SetSize(20) ? "Success" : "Rejected")
        << endl;

    cout << "Set cursor X to -5: "
        << (cursor1.SetX(-5) ? "Success" : "Rejected")
        << endl;

    cout << "Set empty window title: "
        << (windows[0].SetTitle("") ? "Success" : "Rejected")
        << endl;

    cout << "\nProgram finished successfully.\n";

    return 0;
}
