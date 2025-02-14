//
// Created by msullivan on 2/13/25.
//

#include "MathUtils.h"

int MathUtils::sumRange(int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++) // Bug: Off-by-one error (fixed by replacing < with <=)
        sum += i;
    return sum;
}

bool MathUtils::containsNegative(const std::vector<int>& numbers)
{
    for (const int number : numbers) // Bug (fixed by using range-based for-loop)
    {
        if (number < 0) // Bug (fixed by replacing > with <)
        {
            return true;
        }
    }
    return false;
}

int MathUtils::findMax(const std::vector<int>& numbers)
{
    if (numbers.empty()) return 0; // Bug
    int maxVal = numbers[0];
    for (std::size_t i = 1; i <= numbers.size(); i++) // Bug
    {
        if (numbers[i] >= maxVal) // Bug
        {
            maxVal = numbers[i];
        }
    }
    return maxVal;
}