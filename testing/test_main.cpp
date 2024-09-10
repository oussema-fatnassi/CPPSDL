// testing/test_math_functions.cpp
#include <gtest/gtest.h>
#include "math.hpp"

// Test the add function
TEST(AddFunctionTest, HandlesPositiveInput) {
    EXPECT_EQ(add(1, 2), 3);
}

TEST(AddFunctionTest, HandlesNegativeInput) {
    EXPECT_EQ(add(-1, -2), -3);
}

TEST(AddFunctionTest, HandlesMixedInput) {
    EXPECT_EQ(add(-1, 1), 0);
}
