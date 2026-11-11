#include "Equations.h"
#include <iostream>
#include <cmath>

Equation::Equation(double a, double b) : a(a), b(b) {}

Equation::~Equation() {}

LinearEquation::LinearEquation(double a, double b) : Equation(a, b) {}

int LinearEquation::koreni_rivnyannya(double& x1, double& x2) const {
    if (a == 0)
        return (b == 0) ? -1 : 0;
    x1 = -b / a;
    x2 = x1;
    return 1;
}

void LinearEquation::show() const {
    std::cout << a << "*x + " << b << " = 0";
}

QuadraticEquation::QuadraticEquation(double a, double b, double c)
    : Equation(a, b), c(c) {
}

int QuadraticEquation::koreni_rivnyannya(double& x1, double& x2) const {
    if (a == 0) {                     
        if (b == 0)
            return (c == 0) ? -1 : 0;
        x1 = x2 = -c / b;
        return 1;
    }
    double d = b * b - 4 * a * c;
    if (d < 0)
        return 0;
    if (d == 0) {
        x1 = x2 = -b / (2 * a);
        return 1;
    }
    double sq = std::sqrt(d);
    x1 = (-b + sq) / (2 * a);
    x2 = (-b - sq) / (2 * a);
    return 2;
}

void QuadraticEquation::show() const {
    std::cout << a << "*x^2 + " << b << "*x + " << c << " = 0";
}