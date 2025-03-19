//
// Created by msullivan on 3/6/25.
//

#pragma once
#include <string>

class Fraction {
    mutable int num {};
    mutable int den {};

public:
    explicit Fraction(int n = 0, int d = 1);
    virtual ~Fraction() = default;

    [[nodiscard]] int numerator() const { return num; }
    [[nodiscard]] int denominator() const { return den; }

    void setNumerator(int n);
    void setDenominator(int d);
    [[nodiscard]] virtual std::string toString();

    friend Fraction operator+(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator-(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator*(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator/(const Fraction &lhs, const Fraction &rhs);
    friend Fraction &operator+=(const Fraction &lhs, const Fraction &rhs);
    friend Fraction &operator-=(const Fraction &lhs, const Fraction &rhs);
    friend Fraction &operator*=(const Fraction &lhs, const Fraction &rhs);
    friend Fraction &operator/=(const Fraction &lhs, const Fraction &rhs);

private:
    void simplify() const;
};