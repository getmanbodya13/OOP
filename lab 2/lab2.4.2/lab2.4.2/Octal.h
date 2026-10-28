#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

class Octal {
private:
    static const int MAX_SIZE = 100;

    unsigned char digits[MAX_SIZE];
    int size_;                     
    int count_;                  

    void normalize();
    void checkCapacity(int required) const;

    std::vector<int> toVector() const;
    static Octal fromVector(const std::vector<int>& value);

    static int compareVectors(
        const std::vector<int>& a,
        const std::vector<int>& b
    );

    static std::vector<int> addVectors(
        const std::vector<int>& a,
        const std::vector<int>& b
    );

    static std::vector<int> subtractVectors(
        const std::vector<int>& a,
        const std::vector<int>& b
    );

    static std::vector<int> multiplyVectors(
        const std::vector<int>& a,
        const std::vector<int>& b
    );

    static std::pair<std::vector<int>, std::vector<int>> divideVectors(
        const std::vector<int>& a,
        const std::vector<int>& b
    );

public:
    class DigitProxy {
    private:
        Octal& object;
        int index;

    public:
        DigitProxy(Octal& obj, int i);

        DigitProxy& operator=(unsigned char value);
        DigitProxy& operator=(const DigitProxy& other);
        operator unsigned char() const;
    };

    Octal();
    explicit Octal(int maxSize);
    Octal(int maxSize, const std::string& value);
    Octal(const Octal& other);

    int size() const;
    int count() const;
    unsigned char getDigit(int index) const;
    void setDigit(int index, unsigned char value);

    Octal& operator=(const Octal& other);

    DigitProxy operator[](int index);
    unsigned char operator[](int index) const;

    explicit operator std::string() const;

    friend Octal operator+(const Octal& a, const Octal& b);
    friend Octal operator-(const Octal& a, const Octal& b);
    friend Octal operator*(const Octal& a, const Octal& b);
    friend Octal operator/(const Octal& a, const Octal& b);
    friend Octal operator%(const Octal& a, const Octal& b);

    friend bool operator==(const Octal& a, const Octal& b);
    friend bool operator!=(const Octal& a, const Octal& b);
    friend bool operator<(const Octal& a, const Octal& b);
    friend bool operator>(const Octal& a, const Octal& b);
    friend bool operator<=(const Octal& a, const Octal& b);
    friend bool operator>=(const Octal& a, const Octal& b);

    Octal& operator++();
    Octal operator++(int);
    Octal& operator--();
    Octal operator--(int);

    friend std::ostream& operator<<(std::ostream& out, const Octal& value);
    friend std::istream& operator>>(std::istream& in, Octal& value);
};
