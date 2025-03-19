//
// Created by msullivan on 3/6/25.
//

#include "Fraction.h"
#include <stdexcept>

Fraction::Fraction(const int n, const int d) : num(n), den(d)
{
    if (d == 0) throw std::invalid_argument("Denominator cannot be 0");
}

void Fraction::setNumerator(const int n) const
{
    num = n;
    simplify();
}

void Fraction::setDenominator(const int d) const
{
    if (d == 0) throw std::invalid_argument("Denominator cannot be 0");
    den = d;
    simplify();
}

std::string Fraction::toString() const
{
    simplify();
    return std::to_string(num) + '/' + std::to_string(den);
}


void Fraction::simplify() const
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
    return Fraction(lhs.num * rhs.den + rhs.num * lhs.den, lhs.den * rhs.den);
}

Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.num * rhs.den - rhs.num * lhs.den, lhs.den * rhs.den);
}

Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
    return Fraction(lhs.num * rhs.num, lhs.den * rhs.den);
}

Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
    if (rhs.num == 0) throw std::invalid_argument("Cannot divide by 0");
    return Fraction(lhs.num * rhs.den, lhs.den * rhs.num);
}

Fraction &Fraction::operator+=(const Fraction &rhs)
{
    num = num * rhs.den + rhs.num * den;
    den *= rhs.den;
    simplify();
    return *this;
}

Fraction &Fraction::operator-=(const Fraction &rhs)
{
    num = num * rhs.den - rhs.num * den;
    den *= rhs.den;
    simplify();
    return *this;
}

Fraction &Fraction::operator*=(const Fraction &rhs)
{
    num *= rhs.num;
    den *= rhs.den;
    simplify();
    return *this;
}

Fraction &Fraction::operator/=(const Fraction &rhs)
{
    if (rhs.num == 0) throw std::invalid_argument("Cannot divide by 0");
    num *= rhs.den;
    den *= rhs.num;
    simplify();
    return *this;
}