#ifndef TEST_COMPARISON_HPP
#define TEST_COMPARISON_HPP

#include <gtest/gtest.h>

#include "vector.h"

using namespace std;

template <typename T>
class ComparisonTest : public ::testing::Test {};

using TestType = ::testing::Types<int, double, size_t>;

TYPED_TEST_SUITE(ComparisonTest, TestType);

TYPED_TEST(ComparisonTest, EqualComparison_Num) 
{
    Vector<TypeParam> vec1 = {TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec2 = {TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec3 = {TypeParam(1), TypeParam(4), TypeParam(3)};

    bool res1 = (vec1 == vec2);
    bool res2 = (vec1 == vec3);

    EXPECT_EQ(res1, true);
    EXPECT_EQ(res2, false);
}

TEST(ComparisonTest, EqualComparison_SameType) 
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<double> vec2 = {1.0, 2.0, 3.0};

    EXPECT_EQ(vec1 == vec2, true);
}

TEST(ComparisonTest, EqualComparison_Str) 
{
    Vector<string> vec1 = {"apple", "banana", "strawberry"};
    Vector<string> vec2 = {"apple", "banana", "strawberry"};
    Vector<string> vec3 = {"apple", "cherry", "strawberry"};

    bool res1 = (vec1 == vec2);
    bool res2 = (vec1 == vec3);

    EXPECT_EQ(res1, true);
    EXPECT_EQ(res2, false);
}

TYPED_TEST(ComparisonTest, NotEqualComparison_Num) 
{
    Vector<TypeParam> vec1 = {TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec2 = {TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec3 = {TypeParam(1), TypeParam(4), TypeParam(3)};

    bool res1 = (vec1 != vec2);
    bool res2 = (vec1 != vec3);

    EXPECT_EQ(res1, false);
    EXPECT_EQ(res2, true);
}

TEST(ComparisonTest, NotEqualComparison_SameType) 
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<double> vec2 = {6.7, 6.7, 6.7};


    EXPECT_EQ(vec1 != vec2, true);
}

TEST(ComparisonTest, NotEqualComparison_Str) 
{
    Vector<string> vec1 = {"apple", "banana", "strawberry"};
    Vector<string> vec2 = {"apple", "banana", "strawberry"};
    Vector<string> vec3 = {"apple", "cherry", "strawberry"};

    bool res1 = (vec1 != vec2);
    bool res2 = (vec1 != vec3);

    EXPECT_EQ(res1, false);
    EXPECT_EQ(res2, true);
}

#endif
