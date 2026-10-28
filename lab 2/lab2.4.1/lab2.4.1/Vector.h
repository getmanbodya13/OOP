#pragma once

#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

class Vector
{
private:
    int* data;
    int n;

public:
    Vector();
    explicit Vector(int size);
    Vector(initializer_list<int> values);
    Vector(const Vector& other);

    ~Vector();

    int getSize() const;
    int getElement(int index) const;
    void setElement(int index, int value);

    Vector& operator=(const Vector& other);
    int& operator[](int index);
    const int& operator[](int index) const;

    Vector& operator++();
    Vector operator++(int);
    Vector& operator--();
    Vector operator--(int);

    operator string() const;

    int norm() const;

    friend Vector operator+(const Vector& left, const Vector& right);
    friend bool operator==(const Vector& left, const Vector& right);
    friend bool operator!=(const Vector& left, const Vector& right);

    friend ostream& operator<<(ostream& out, const Vector& v);
    friend istream& operator>>(istream& in, Vector& v);
};