#include "Octal.h"

#include <cctype>
#include <utility>

using namespace std;

Octal::Octal() : size_(MAX_SIZE), count_(1) {
    fill(digits, digits + MAX_SIZE, 0);
}

Octal::Octal(int maxSize) : size_(maxSize), count_(1) {
    if (maxSize < 1 || maxSize > MAX_SIZE)
        throw invalid_argument("Invalid maximum size");

    fill(digits, digits + MAX_SIZE, 0);
}

Octal::Octal(int maxSize, const string& value)
    : size_(maxSize), count_(1) {
    if (maxSize < 1 || maxSize > MAX_SIZE)
        throw invalid_argument("Invalid maximum size");

    fill(digits, digits + MAX_SIZE, 0);

    if (value.empty())
        throw invalid_argument("Empty octal number");

    if (static_cast<int>(value.size()) > size_)
        throw length_error("Number exceeds object capacity");

    count_ = static_cast<int>(value.size());

    for (int i = 0; i < count_; ++i) {
        char c = value[value.size() - 1 - i];

        if (c < '0' || c > '7')
            throw invalid_argument("Only digits 0-7 are allowed");

        digits[i] = static_cast<unsigned char>(c - '0');
    }

    normalize();
}

Octal::Octal(const Octal& other)
    : size_(other.size_), count_(other.count_) {
    copy(other.digits, other.digits + MAX_SIZE, digits);
}

Octal& Octal::operator=(const Octal& other) {
    if (this != &other) {
        size_ = other.size_;
        count_ = other.count_;
        copy(other.digits, other.digits + MAX_SIZE, digits);
    }
    return *this;
}

int Octal::size() const {
    return size_;
}

int Octal::count() const {
    return count_;
}

unsigned char Octal::getDigit(int index) const {
    if (index < 0 || index >= count_)
        throw out_of_range("Digit index out of range");

    return digits[index];
}

void Octal::setDigit(int index, unsigned char value) {
    if (index < 0 || index >= size_)
        throw out_of_range("Digit index out of range");

    if (value > 7)
        throw invalid_argument("An octal digit must be from 0 to 7");

    digits[index] = value;

    if (index >= count_)
        count_ = index + 1;

    normalize();
}

void Octal::checkCapacity(int required) const {
    if (required > size_ || required > MAX_SIZE)
        throw overflow_error("Octal number exceeds capacity");
}

void Octal::normalize() {
    while (count_ > 1 && digits[count_ - 1] == 0)
        --count_;
}

Octal::DigitProxy::DigitProxy(Octal& obj, int i)
    : object(obj), index(i) {
}

Octal::DigitProxy& Octal::DigitProxy::operator=(unsigned char value) {
    object.setDigit(index, value);
    return *this;
}

Octal::DigitProxy& Octal::DigitProxy::operator=(
    const DigitProxy& other) {
    return *this = static_cast<unsigned char>(other);
}

Octal::DigitProxy::operator unsigned char() const {
    return object.getDigit(index);
}

Octal::DigitProxy Octal::operator[](int index) {
    if (index < 0 || index >= size_)
        throw out_of_range("Digit index out of range");

    return DigitProxy(*this, index);
}

unsigned char Octal::operator[](int index) const {
    return getDigit(index);
}

Octal::operator string() const {
    string result;

    for (int i = count_ - 1; i >= 0; --i)
        result += static_cast<char>('0' + digits[i]);

    return result;
}

vector<int> Octal::toVector() const {
    vector<int> result;

    for (int i = 0; i < count_; ++i)
        result.push_back(digits[i]);

    return result;
}

Octal Octal::fromVector(const vector<int>& value) {
    if (value.empty() || value.size() > MAX_SIZE)
        throw overflow_error("Invalid result size");

    Octal result(MAX_SIZE);

    result.count_ = static_cast<int>(value.size());

    for (int i = 0; i < result.count_; ++i)
        result.digits[i] = static_cast<unsigned char>(value[i]);

    result.normalize();
    return result;
}

int Octal::compareVectors(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size())
        return a.size() < b.size() ? -1 : 1;

    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
        if (a[i] != b[i])
            return a[i] < b[i] ? -1 : 1;
    }

    return 0;
}

vector<int> Octal::addVectors(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int carry = 0;
    size_t length = max(a.size(), b.size());

    for (size_t i = 0; i < length || carry; ++i) {
        int sum = carry;

        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];

        result.push_back(sum % 8);
        carry = sum / 8;
    }

    return result;
}

vector<int> Octal::subtractVectors(
    const vector<int>& a, const vector<int>& b) {
    if (compareVectors(a, b) < 0)
        throw underflow_error("Unsigned subtraction would be negative");

    vector<int> result;
    int borrow = 0;

    for (size_t i = 0; i < a.size(); ++i) {
        int digit = a[i] - borrow;
        borrow = 0;

        if (i < b.size())
            digit -= b[i];

        if (digit < 0) {
            digit += 8;
            borrow = 1;
        }

        result.push_back(digit);
    }

    while (result.size() > 1 && result.back() == 0)
        result.pop_back();

    return result;
}

vector<int> Octal::multiplyVectors(
    const vector<int>& a, const vector<int>& b) {
    vector<int> result(a.size() + b.size(), 0);

    for (size_t i = 0; i < a.size(); ++i) {
        int carry = 0;

        for (size_t j = 0; j < b.size() || carry; ++j) {
            long long current = result[i + j] + carry;

            if (j < b.size())
                current += static_cast<long long>(a[i]) * b[j];

            result[i + j] = static_cast<int>(current % 8);
            carry = static_cast<int>(current / 8);
        }
    }

    while (result.size() > 1 && result.back() == 0)
        result.pop_back();

    return result;
}

pair<vector<int>, vector<int>> Octal::divideVectors(
    const vector<int>& a, const vector<int>& b) {
    if (b.size() == 1 && b[0] == 0)
        throw domain_error("Division by zero");

    vector<int> quotient(a.size(), 0);
    vector<int> remainder(1, 0);

    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
        remainder.insert(remainder.begin(), a[i]);

        while (remainder.size() > 1 && remainder.back() == 0)
            remainder.pop_back();

        int q = 0;

        while (compareVectors(remainder, b) >= 0) {
            remainder = subtractVectors(remainder, b);
            ++q;
        }

        quotient[i] = q;
    }

    while (quotient.size() > 1 && quotient.back() == 0)
        quotient.pop_back();

    while (remainder.size() > 1 && remainder.back() == 0)
        remainder.pop_back();

    return { quotient, remainder };
}


Octal operator+(const Octal& a, const Octal& b) {
    return Octal::fromVector(
        Octal::addVectors(a.toVector(), b.toVector()));
}

Octal operator-(const Octal& a, const Octal& b) {
    return Octal::fromVector(
        Octal::subtractVectors(a.toVector(), b.toVector()));
}

Octal operator*(const Octal& a, const Octal& b) {
    return Octal::fromVector(
        Octal::multiplyVectors(a.toVector(), b.toVector()));
}

Octal operator/(const Octal& a, const Octal& b) {
    return Octal::fromVector(
        Octal::divideVectors(a.toVector(), b.toVector()).first);
}

Octal operator%(const Octal& a, const Octal& b) {
    return Octal::fromVector(
        Octal::divideVectors(a.toVector(), b.toVector()).second);
}


bool operator==(const Octal& a, const Octal& b) {
    return Octal::compareVectors(a.toVector(), b.toVector()) == 0;
}

bool operator!=(const Octal& a, const Octal& b) {
    return !(a == b);
}

bool operator<(const Octal& a, const Octal& b) {
    return Octal::compareVectors(a.toVector(), b.toVector()) < 0;
}

bool operator>(const Octal& a, const Octal& b) {
    return b < a;
}

bool operator<=(const Octal& a, const Octal& b) {
    return !(a > b);
}

bool operator>=(const Octal& a, const Octal& b) {
    return !(a < b);
}


Octal& Octal::operator++() {
    *this = *this + Octal(1, "1");
    checkCapacity(count_);
    return *this;
}

Octal Octal::operator++(int) {
    Octal old(*this);
    ++(*this);
    return old;
}

Octal& Octal::operator--() {
    *this = *this - Octal(1, "1");
    return *this;
}

Octal Octal::operator--(int) {
    Octal old(*this);
    --(*this);
    return old;
}

ostream& operator<<(ostream& out, const Octal& value) {
    return out << static_cast<string>(value);
}

istream& operator>>(istream& in, Octal& value) {
    string input;
    in >> input;

    try {
        Octal temp(value.size_, input);
        value = temp;
    }
    catch (const exception&) {
        in.setstate(ios::failbit);
    }

    return in;
}
