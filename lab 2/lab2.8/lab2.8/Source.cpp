#include "ModelWindow.h"
#include <limits>
#pragma pack(push, 1)
struct PackedModelWindow
{
    string title;
    int x, y;
    int width, height;
    string color;
    bool visible;
    bool border;
    ModelWindow::Cursor cursor;
};
#pragma pack(pop)

int main()
{
    cout << "\n--- 1. Constructors ---" << endl;

    ModelWindow w1;

    ModelWindow::Cursor c1(
        100, 150,
        ModelWindow::Cursor::Horizontal,
        5
    );

    ModelWindow w2(
        "Main Window",
        100, 100,
        800, 600,
        "Blue",
        true, true,
        c1
    );

    ModelWindow w3(w2);

    cout << "\nObject w1:" << endl;
    w1.Display();

    cout << "\nObject w2:" << endl;
    w2.Display();

    cout << "\nObject w3 (copy):" << endl;
    w3.Display();

    cout << "\n--- 2. Assignment operator ---" << endl;

    ModelWindow w4;
    w4 = w2;

    cout << w4 << endl;

    cout << "\n--- 3. Moving window ---" << endl;

    w2.moveHorizontal(50);
    w2.moveVertical(30);

    w2.Display();

    w2.moveHorizontal(2000);

    cout << "\n--- 4. Resize window ---" << endl;

    w2.resize(900, 700);
    w2.Display();

    w2.resize(3000, 2000);

    cout << "\n--- 5. Change color and state ---" << endl;

    w2.changeColor("Red");
    w2.setVisible(false);
    w2.setBorder(false);

    w2.Display();

    cout << "\n--- 6. Increment operations ---" << endl;

    cout << "Before: " << w3.getX()
        << ", " << w3.getY() << endl;

    ++w3;

    cout << "Prefix ++: " << w3.getX()
        << ", " << w3.getY() << endl;

    w3++;

    cout << "Postfix ++: " << w3.getX()
        << ", " << w3.getY() << endl;

    cout << "\n--- 7. Decrement operations ---" << endl;

    --w3;

    cout << "Prefix --: " << w3.getX()
        << ", " << w3.getY() << endl;

    w3--;

    cout << "Postfix --: " << w3.getX()
        << ", " << w3.getY() << endl;

    cout << "\n--- 8. Nested Cursor class ---" << endl;

    ModelWindow::Cursor c2;

    c2.setCoordinates(200, 300);
    c2.setType(ModelWindow::Cursor::Vertical);
    c2.setSize(10);

    cout << c2 << endl;

    ++c2;
    cout << "After prefix ++: " << c2 << endl;

    c2++;
    cout << "After postfix ++: " << c2 << endl;

    --c2;
    cout << "After prefix --: " << c2 << endl;

    c2--;
    cout << "After postfix --: " << c2 << endl;

    c2.erase();
    cout << "After erase: " << c2 << endl;

    c2.restore();
    cout << "After restore: " << c2 << endl;

    ModelWindow::Cursor c3;
    c3 = c2;

    cout << "Assigned cursor: " << c3 << endl;

    cout << "\n--- 9. Getters ---" << endl;

    cout << "Title: " << w2.getTitle() << endl;
    cout << "X: " << w2.getX() << endl;
    cout << "Y: " << w2.getY() << endl;
    cout << "Width: " << w2.getWidth() << endl;
    cout << "Height: " << w2.getHeight() << endl;
    cout << "Color: " << w2.getColor() << endl;
    cout << "Visible: " << w2.isVisible() << endl;
    cout << "Border: " << w2.hasBorder() << endl;

    string str = static_cast<string>(w2);

    cout << "\nObject as string:" << endl;
    cout << str << endl;

    cout << "\n--- 10. Array of ModelWindow objects ---" << endl;

    ModelWindow windows[3];

    for (int i = 0; i < 3; i++)
    {
        cout << "\nWindow " << i + 1 << ":" << endl;
        windows[i].Display();
    }
    ModelWindow copiedWindows[2] = { w2, w3 };

    cout << "\nArray of copied objects:" << endl;

    for (int i = 0; i < 2; i++)
    {
        copiedWindows[i].Display();
    }

    cout << "\n--- 11. Keyboard input ---" << endl;

    ModelWindow inputWindow;

    cout << "Enter window parameters:" << endl;
    cin >> inputWindow;

    if (cin)
    {
        cout << "\nEntered window:" << endl;
        cout << inputWindow << endl;
    }
    else
    {
        cout << "Invalid window data!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ModelWindow::Cursor inputCursor;

    cout << "\nEnter cursor parameters:" << endl;
    cin >> inputCursor;

    if (cin)
    {
        cout << "\nEntered cursor:" << endl;
        cout << inputCursor << endl;
    }
    else
    {
        cout << "Invalid cursor data!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\n--- 12. Object counters ---" << endl;

    cout << "ModelWindow objects: "
        << ModelWindow::getCounter() << endl;

    cout << "Cursor objects: "
        << ModelWindow::Cursor::getCounter() << endl;

    cout << "\n--- 13. Class sizes ---" << endl;

    cout << "ModelWindow without pack(1): "
        << sizeof(ModelWindow) << " bytes" << endl;

    cout << "ModelWindow with pack(1): "
        << sizeof(PackedModelWindow) << " bytes" << endl;

    cout << "Cursor: "
        << sizeof(ModelWindow::Cursor) << " bytes" << endl;
    return 0;
}
