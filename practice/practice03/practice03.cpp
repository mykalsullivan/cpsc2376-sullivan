//
// Created by msullivan on 2/13/25.
//

// practice03.cpp (Buggy Code to be tested)
#include "MathUtils.h"
#include <iostream>

int main()
{
    std::cout << "Sum from 1 to 5: " << MathUtils::sumRange(1, 5) << std::endl;
    std::vector<int> values = {3, -1, 5, 7};
    std::cout << "Contains negative? " << MathUtils::containsNegative(values) << std::endl;
    std::cout << "Max value: " << MathUtils::findMax(values) << std::endl;
}