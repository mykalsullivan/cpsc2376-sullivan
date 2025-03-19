//
// Created by msullivan on 3/6/25.
//

#pragma once
#include <string>

class Fraction {
protected:
    mutable int num {};
    mutable int den {};

public:
    explicit Fraction(int n = 0, int d = 1);
    virtual ~Fraction() = default;

    [[nodiscard]] int numerator() const { return num; }
    [[nodiscard]] int denominator() const { return den; }

    void setNumerator(int n) const;
    void setDenominator(int d) const;
    [[nodiscard]] virtual std::string toString() const;

    friend Fraction operator+(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator-(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator*(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator/(const Fraction &lhs, const Fraction &rhs);

    Fraction &operator+=(const Fraction &rhs);
    Fraction &operator-=(const Fraction &rhs);
    Fraction &operator*=(const Fraction &rhs);
    Fraction &operator/=(const Fraction &rhs);

private:
    void simplify() const;
};