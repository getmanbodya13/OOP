#include <iostream>
#include <typeinfo>
#include "Equations.h"

using namespace std;

const char* type_name(const Equation& e) {
    if (typeid(e) == typeid(LinearEquation))
        return "Linear equation (class LinearEquation)";
    if (typeid(e) == typeid(QuadraticEquation))
        return "Quadratic equation (class QuadraticEquation)";
    return "Unknown type";
}

int main() {
    const int N = 5;
    Equation* arr[N];
    arr[0] = new LinearEquation(2, -4);
    arr[1] = new QuadraticEquation(1, -5, 6);
    arr[2] = new QuadraticEquation(1, 2, 1);
    arr[3] = new QuadraticEquation(1, 0, 4);
    arr[4] = new LinearEquation(0, 5);

    for (int i = 0; i < N; i++) {
        double x1 = 0, x2 = 0;

        cout << "Object " << i + 1 << endl;
        cout << "  Real type: " << type_name(*arr[i]) << endl;
        cout << "  Equation: ";
        arr[i]->show();
        cout << endl;

        int n = arr[i]->koreni_rivnyannya(x1, x2);  
        switch (n) {
        case -1: cout << "  Infinitely many solutions" << endl; break;
        case 0:  cout << "  No real roots" << endl; break;
        case 1:  cout << "  One root: x = " << x1 << endl; break;
        case 2:  cout << "  Two roots: x1 = " << x1
            << ", x2 = " << x2 << endl; break;
        }
        cout << endl;
    }

    for (int i = 0; i < N; i++)
        delete arr[i];

    return 0;
}