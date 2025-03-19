//
// Created by msullivan on 3/6/25.
//

#include "MixedFraction.h"
#include <stdexcept>
#include <iostream>

MixedFraction::MixedFraction(const int whole, const int n, const int d) : Fraction(n, d), m_Whole(whole)
{
    if (d == 0) throw std::invalid_argument("Denominator cannot be 0");
    convertToMixed(); // Ensure proper representation
}

MixedFraction::MixedFraction(const Fraction &fraction) : Fraction(fraction)
{
    convertToMixed();
}

void MixedFraction::convertToMixed()
{
    if (num >= den)
    {
        m_Whole += num / den;
        num %= den;
    }
}

std::string MixedFraction::toString() const
{
    if (num == 0) return std::to_string(m_Whole);
    if (m_Whole == 0) return Fraction::toString();
    return std::to_string(m_Whole) + " " + std::to_string(num) + "/" + std::to_string(den);
}

std::ostream &operator<<(std::ostream &out, const MixedFraction &mixedFraction)
{
    if (mixedFraction.m_Whole != 0)
    {
        out << mixedFraction.m_Whole; // Print m_m_Whole number part
        if (mixedFraction.numerator() != 0)
            out << " " << mixedFraction.numerator() << "/" << mixedFraction.denominator(); // Print fraction part
    } 
    else
        out << mixedFraction.numerator() << "/" << mixedFraction.denominator(); // Print fraction only
    return out;
}
