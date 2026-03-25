#ifndef TEST_UNARY_HPP
#define TEST_UNARY_HPP

#include <gtest/gtest.h>

#include "vector.h"
#include <math.h>

using namespace std;

template <typename T>
class UnaryTest : public ::testing::Test {};

using TestType = ::testing::Types<int, double, size_t>;

TYPED_TEST_SUITE(UnaryTest, TestType);

TYPED_TEST(UnaryTest, LengthUnary_Num) 
{
    TypeParam a = 1;
    TypeParam b = 2;
    TypeParam c = 5;
    Vector<TypeParam> vec = {a, b, c};
    
    double len = vec.length();

    EXPECT_EQ(len, sqrt(a*a + b*b + c*c));
}

TYPED_TEST(UnaryTest, LengthExceptionUnary_Num) 
{
    Vector<TypeParam> vec;
    
    EXPECT_THROW(vec.length(), EmptyVectorException);
}


TYPED_TEST(UnaryTest, NotEqualUnary_Num) 
{
    Vector<TypeParam> vec1 = {TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec2 = {TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec3 = {TypeParam(1), TypeParam(4), TypeParam(3)};

    bool res1 = (vec1 != vec2);
    bool res2 = (vec1 != vec3);

    EXPECT_EQ(res1, false);
    EXPECT_EQ(res2, true);
}

TEST(UnaryTest, NotEqualUnary_Str) 
{
    Vector<string> vec1 = {"apple", "banana", "strawberry"};
    Vector<string> vec2 = {"apple", "banana", "strawberry"};
    Vector<string> vec3 = {"apple", "cherry", "strawberry"};

    bool res1 = (vec1 != vec2);
    bool res2 = (vec1 != vec3);

    EXPECT_EQ(res1, false);
    EXPECT_EQ(res2, true);
}

TYPED_TEST(UnaryTest, getUnit_Num)
{
    Vector<TypeParam> vec = {TypeParam(4), TypeParam(3)};
    Vector<double> needVec = {0.8, 0.6};
    Vector<double> resVec = vec.getUnit();

    EXPECT_EQ(needVec == resVec, true);
}

TEST(UnaryTest, getUnit_ZeroSize)
{
    Vector<int> vec = {};

    EXPECT_THROW(vec.getUnit(), EmptyVectorException);
}

TYPED_TEST(UnaryTest, at)
{
    Vector<TypeParam> vec = {TypeParam(4), TypeParam(3)};

    EXPECT_EQ(vec.at(0), 4);
    EXPECT_EQ(vec.at(1), 3);
}

TEST(UnaryTest, at_badIndex)
{
    Vector<int> vec = {4, 3};

    EXPECT_THROW(vec.at(4), OutOfRangesException);
}

TYPED_TEST(UnaryTest, test_brackets)
{
    Vector<TypeParam> vec = {TypeParam(4)};

    EXPECT_EQ(vec[0], TypeParam(4));
}

TEST(UnaryTest, bad_brackets)
{
    Vector<int> vec = {4, 3};

    EXPECT_THROW(vec[5], OutOfRangesException);
}

TYPED_TEST(UnaryTest, const_at)
{
    const Vector<TypeParam> vec = {TypeParam(4), TypeParam(3)};

    EXPECT_EQ(vec.at(0), 4);
    EXPECT_EQ(vec.at(1), 3);
}

TEST(UnaryTest, const_at_badIndex)
{
    const Vector<int> vec = {4, 3};

    EXPECT_THROW(vec.at(4), OutOfRangesException);
}

TYPED_TEST(UnaryTest, const_test_brackets)
{
    const Vector<TypeParam> vec = {TypeParam(4)};

    EXPECT_EQ(vec[0], TypeParam(4));
}

TEST(UnaryTest, const_bad_brackets)
{
    const Vector<int> vec = {4, 3};

    EXPECT_THROW(vec[5], OutOfRangesException);
}

#endif
