//
// Created by msullivan on 3/6/25.
//

#include "Fraction.h"
#include <stdexcept>

Fraction::Fraction(const int n, const int d) : num(n), den(d)
{
    if (d == 0) throw std::invalid_argument("Denominator cannot be 0");
}

void Fraction::setNumerator(const int n)
{
    num = n;
    simplify();
}

void Fraction::setDenominator(const int d)
{
    if (d == 0) throw std::invalid_argument("Denominator cannot be 0");
    den = d;
    simplify();
}

std::string Fraction::toString()
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
    Fraction newFrac {};
    lhs.num *= rhs.den;
    rhs.num *= lhs.den;
    newFrac.den = lhs.den * rhs.den;
    newFrac.num = lhs.num + rhs.num;
    newFrac.simplify();
    return newFrac;
}

Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
    Fraction newFrac {};
    lhs.num *= rhs.den;
    rhs.num *= lhs.den;
    newFrac.den = lhs.den * rhs.den;
    newFrac.num = lhs.num - rhs.num;
    newFrac.simplify();
    return newFrac;
}

Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
    Fraction newFrac {};
    lhs.num *= rhs.den;
    rhs.num *= lhs.den;
    newFrac.den = lhs.den * rhs.den;
    newFrac.num = lhs.num * rhs.num;
    newFrac.simplify();
    return newFrac;
}

Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
    Fraction newFrac {};

    if (rhs.den == 0) throw std::invalid_argument("Cannot divide by 0");

    const int commonDenominator = lhs.den * rhs.den;
    lhs.num *= rhs.den;
    rhs.num *= lhs.den;
    newFrac.den = commonDenominator;
    newFrac.num = lhs.num / rhs.num;
    newFrac.simplify();
    return newFrac;
}

Fraction &operator+=(const Fraction &lhs, const Fraction &rhs)
{
    Fraction newFrac {};
    newFrac.num = lhs.num + rhs.num;
    newFrac.den = lhs.den + rhs.den;
    newFrac.simplify();
    return newFrac;
}

Fraction &operator-=(const Fraction &lhs, const Fraction &rhs)
{
    Fraction newFrac {};
    newFrac.num = lhs.num - rhs.num;
    newFrac.den = lhs.den - rhs.den;
    newFrac.simplify();
    return newFrac;
}

Fraction &operator*=(const Fraction &lhs, const Fraction &rhs)
{
    Fraction newFrac {};
    newFrac.num = lhs.num * rhs.num;
    newFrac.den = lhs.den * rhs.den;
    newFrac.simplify();
    return newFrac;
}

Fraction &operator/=(const Fraction &lhs, const Fraction &rhs)
{
    Fraction newFrac {};
    newFrac.num = lhs.num / rhs.num;
    newFrac.den = lhs.den / rhs.den;
    newFrac.simplify();
    return newFrac;
}