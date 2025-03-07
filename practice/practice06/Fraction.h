//
// Created by msullivan on 3/6/25.
//

#pragma once

class Fraction {
    int num {};
    int den {};

public:
    explicit Fraction(const int n = 0, const int d = 1) : num(n), den(d)
    {
        if (d == 0) throw std::invalid_argument("Denominator cannot be 0");
    }

    ~Fraction() = default;

    [[nodiscard]] int numerator() const { return num; }
    [[nodiscard]] int denominator() const { return den; }

    void setNumerator(const int n)
    {
        num = n;
    }
    void setDenominator(const int d)
    {
        if (d == 0) throw std::invalid_argument("Denominator cannot be 0");
        den = d;
    }

    void simplify()
    {
        int a = num, b = den;
        while (b != 0)
        {
            const int temp = b;
            b = a % b;
            a = temp;
        }

        const int gcd = a;

        num /= gcd;
        den /= gcd;
    }

    Fraction operator+(const Fraction &lhs, const Fraction &rhs)
    {

    }

    Fraction operator-(const Fraction &lhs, const Fraction &rhs)
    {

    }

    Fraction operator*(const Fraction &lhs, const Fraction &rhs)
    {

    }

    Fraction operator/(const Fraction &lhs, const Fraction &rhs)
    {

    }
};