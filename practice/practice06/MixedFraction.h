//
// Created by msullivan on 3/6/25.
//

#pragma once
#include "Fraction.h"

class MixedFraction : public Fraction {

public:
    MixedFraction(int whole, const int n, const int d);
    MixedFraction(const Fraction &fraction);
    ~MixedFraction() = default;

    void operator<<(const Fraction &fraction);
};