//
// Created by msullivan on 2/13/25.
//

#include <gtest/gtest.h>
#include "MathUtils.h"

namespace {
    const std::vector g_Values {3, -1, 5, 7};
}

TEST(MathUtilsTest, SumRange_CorrectSum)
{
    EXPECT_EQ(MathUtils::sumRange(1, 5), 15); // 1 + 2 + 3 + 4 + 5 = 15
}

TEST(MathUtilsTest, SumRange_StartEnd)
{
    EXPECT_EQ(MathUtils::sumRange(5, 5), 5);
}

TEST(MathUtilsTest, SumRange_NegativeValues)
{
    EXPECT_NO_THROW(MathUtils::sumRange(-1, -3));
}

TEST(MathUtilsTest, ContainsNegative_OutOfBounds)
{
    EXPECT_TRUE(MathUtils::containsNegative(g_Values)); // There's a negative number, so it should return true.
}

TEST(MathUtilsTest, ContainsNegative_AllPositive)
{
    const std::vector allPositiveVec {5, 4, 3, 2, 1};
    EXPECT_FALSE(MathUtils::containsNegative(allPositiveVec));
}

TEST(MathUtilsTest, ContainsNegative_EmptyList)
{
    EXPECT_FALSE(MathUtils::containsNegative({}));
}

TEST(MathUtilsTest, FindMax_EmptyVector)
{
    EXPECT_EQ(MathUtils::findMax({}), 0); // Should return 0
}

TEST(MathUtilsTest, FindMax_OutOfBounds)
{
    EXPECT_EQ(MathUtils::findMax(g_Values), 7);
}

TEST(MathUtilsTest, FindMax_AllEqual)
{
    const std::vector allEqualVec {5, 5, 5, 5};
    EXPECT_EQ(MathUtils::findMax(allEqualVec), 5);
}

int main(int argc, char **argv)
{
    // Testing
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}