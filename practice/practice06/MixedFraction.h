//
// Created by msullivan on 3/6/25.
//

#pragma once
#include "Fraction.h"

class MixedFraction final : public Fraction {
    int m_Whole {};

public:
    MixedFraction(int whole, int n, int d);
    explicit MixedFraction(const Fraction &fraction);
    ~MixedFraction() override = default;

    [[nodiscard]] std::string toString() const override;
    friend std::ostream &operator<<(std::ostream &out, const MixedFraction &mixedFraction);

private:
    // Helper function to adjust whole and fraction parts
    void convertToMixed();
};