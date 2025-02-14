//
// Created by msullivan on 2/13/25.
//

#pragma once
#include <vector>

class MathUtils {
public:
    static int sumRange(int start, int end);
    static bool containsNegative(const std::vector<int>& numbers);
    static int findMax(const std::vector<int>& numbers);
};