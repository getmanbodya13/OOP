#pragma once
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cctype>
#include <utility>

using namespace std;

class Array
{
public:
    static const int MAX_SIZE = 100;

protected:
    unsigned char digits[MAX_SIZE]{};
    int size;

public:
    Array(int n, unsigned char initial = 0)
    {
        if (n < 1 || n > MAX_SIZE)
            throw out_of_range("Invalid array size");

        size = n;

        for (int i = 0; i < size; i++)
            digits[i] = initial;
    }

    virtual ~Array() = default;

    bool rangeCheck(int index) const
    {
        return index >= 0 && index < size;
    }

    unsigned char& operator[](int index)
    {
        if (!rangeCheck(index))
            throw out_of_range("Array index out of range");

        return digits[index];
    }

    const unsigned char& operator[](int index) const
    {
        if (!rangeCheck(index))
            throw out_of_range("Array index out of range");

        return digits[index];
    }

    int getSize() const
    {
        return size;
    }

    virtual unique_ptr<Array> add(const Array& other) const = 0;
    virtual string typeName() const = 0;

    virtual void print() const = 0;
};

template<int BASE, typename Derived>
class Number : public Array
{
protected:

    void normalize()
    {
        while (size > 1 && digits[size - 1] == 0)
            size--;
    }

    int compare(const Derived& other) const
    {
        if (size != other.size)
            return size < other.size ? -1 : 1;

        for (int i = size - 1; i >= 0; i--)
        {
            if (digits[i] != other.digits[i])
                return digits[i] < other.digits[i] ? -1 : 1;
        }

        return 0;
    }

public:
    Number(int n, unsigned char initial = 0)
        : Array(n, initial)
    {
        if (initial >= BASE)
            throw invalid_argument("Invalid digit for number system");
    }

    Number(const string& value)
        : Array(1, 0)
    {
        if (value.empty() || value.size() > MAX_SIZE)
            throw invalid_argument("Invalid number length");

        size = static_cast<int>(value.size());

        for (int i = 0; i < size; i++)
        {
            char c = toupper(static_cast<unsigned char>(
                value[value.size() - 1 - i]));

            int digit;

            if (c >= '0' && c <= '9')
                digit = c - '0';
            else if (c >= 'A' && c <= 'F')
                digit = c - 'A' + 10;
            else
                throw invalid_argument("Invalid digit");

            if (digit >= BASE)
                throw invalid_argument("Digit exceeds number base");

            digits[i] = static_cast<unsigned char>(digit);
        }

        normalize();
    }

    string toString() const
    {
        string result;

        for (int i = size - 1; i >= 0; i--)
        {
            if (digits[i] < 10)
                result += char('0' + digits[i]);
            else
                result += char('A' + digits[i] - 10);
        }

        return result;
    }

    void print() const override
    {
        cout << typeName() << ": " << toString() << endl;
    }

    string typeName() const override
    {
        if constexpr (BASE == 8)
            return "Octal";
        else
            return "Hex";
    }

    unique_ptr<Array> add(const Array& other) const override
    {
        const Derived* ptr = dynamic_cast<const Derived*>(&other);

        if (ptr == nullptr)
            throw invalid_argument("Incompatible number types");

        return make_unique<Derived>(
            static_cast<const Derived&>(*this) + *ptr
        );
    }

    Derived operator+(const Derived& other) const
    {
        Derived result(1, 0);

        int carry = 0;
        int n = max(size, other.size);

        result.size = n;

        for (int i = 0; i < n; i++)
        {
            int sum = carry;

            if (i < size)
                sum += digits[i];

            if (i < other.size)
                sum += other.digits[i];

            result.digits[i] = sum % BASE;
            carry = sum / BASE;
        }

        if (carry)
        {
            if (n >= MAX_SIZE)
                throw overflow_error("Number overflow");

            result.digits[n] = carry;
            result.size = n + 1;
        }

        result.normalize();
        return result;
    }

    Derived operator-(const Derived& other) const
    {
        if (compare(other) < 0)
            throw underflow_error("Negative unsigned result");

        Derived result(size, 0);

        int borrow = 0;

        for (int i = 0; i < size; i++)
        {
            int diff = digits[i] - borrow;

            if (i < other.size)
                diff -= other.digits[i];

            if (diff < 0)
            {
                diff += BASE;
                borrow = 1;
            }
            else
                borrow = 0;

            result.digits[i] = diff;
        }

        result.normalize();
        return result;
    }

    Derived operator*(const Derived& other) const
    {
        vector<int> temp(size + other.size + 1, 0);

        for (int i = 0; i < size; i++)
        {
            int carry = 0;

            for (int j = 0; j < other.size; j++)
            {
                int current = temp[i + j]
                    + digits[i] * other.digits[j] + carry;

                temp[i + j] = current % BASE;
                carry = current / BASE;
            }

            int k = i + other.size;

            while (carry > 0)
            {
                int current = temp[k] + carry;
                temp[k] = current % BASE;
                carry = current / BASE;
                k++;
            }
        }

        int n = static_cast<int>(temp.size());

        while (n > 1 && temp[n - 1] == 0)
            n--;

        if (n > MAX_SIZE)
            throw overflow_error("Number overflow");

        Derived result(n, 0);

        for (int i = 0; i < n; i++)
            result.digits[i] = temp[i];

        return result;
    }

    pair<Derived, Derived> divmod(const Derived& other) const
    {
        if (other.toString() == "0")
            throw domain_error("Division by zero");

        Derived quotient(size, 0);
        Derived remainder(1, 0);

        for (int i = size - 1; i >= 0; i--)
        {
            if (remainder.size >= MAX_SIZE)
                throw overflow_error("Number overflow");

            for (int j = remainder.size; j > 0; j--)
                remainder.digits[j] = remainder.digits[j - 1];

            remainder.digits[0] = digits[i];
            remainder.size++;

            remainder.normalize();

            int qdigit = 0;

            while (remainder.compare(other) >= 0)
            {
                remainder = remainder - other;
                qdigit++;
            }

            quotient.digits[i] = static_cast<unsigned char>(qdigit);
        }

        quotient.normalize();
        remainder.normalize();

        return { quotient, remainder };
    }

    Derived operator/(const Derived& other) const
    {
        return divmod(other).first;
    }

    Derived operator%(const Derived& other) const
    {
        return divmod(other).second;
    }

    bool operator==(const Derived& other) const
    {
        return compare(other) == 0;
    }

    bool operator!=(const Derived& other) const
    {
        return compare(other) != 0;
    }

    bool operator<(const Derived& other) const
    {
        return compare(other) < 0;
    }

    bool operator>(const Derived& other) const
    {
        return compare(other) > 0;
    }

    bool operator<=(const Derived& other) const
    {
        return compare(other) <= 0;
    }

    bool operator>=(const Derived& other) const
    {
        return compare(other) >= 0;
    }
};

class Octal : public Number<8, Octal>
{
public:
    using Number<8, Octal>::Number;
};

class Hex : public Number<16, Hex>
{
public:
    using Number<16, Hex>::Number;
};
