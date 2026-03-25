#ifndef TEST_ASSIGMENT_HPP
#define TEST_ASSIGMENT_HPP

#include <gtest/gtest.h>

#include "vector.h"

using namespace std;

template <typename T>
class AssignmentTest : public ::testing::Test {};

using TestType = ::testing::Types<int, double, size_t>;

TYPED_TEST_SUITE(AssignmentTest, TestType);

TYPED_TEST(AssignmentTest, Init_ListAssignment_Num) 
{
    Vector<TypeParam> vec;
    vec = {TypeParam(1), TypeParam(2), TypeParam(3)};

    EXPECT_EQ(vec.getSize(), 3);

    ConstIterator<TypeParam> vecIt = vec.cbegin();

    for (TypeParam i = TypeParam(1); vecIt; ++vecIt, ++i)
        EXPECT_EQ(*vecIt, i);
}

TEST(AssignmentTest, Init_ListAssignment_SameType) 
{
    Vector<int> vec;
    vec = {6.7, 6.7, 6.7};

    EXPECT_EQ(vec.getSize(), 3);

    ConstIterator<int> vecIt = vec.cbegin();

    for (; vecIt; ++vecIt)
        EXPECT_EQ(*vecIt, 6);
}

/*TEST(AssignmentTest, Init_ListAssignment_Error) 
{
    Vector<string> vec;
    vec = {"asb", "sag"};

    double len = vec.length();    СЕКРЕТНЫЙ ХАКЕРСКИЙ ТЕСТ НА КОНЦЕПТЫ

    EXPECT_EQ(len, 6);
}*/

TEST(AssignmentTest, Init_ListAssignment_Str) 
{
    Vector<string> vec;
    vec = {"apple", "banana", "strawberry"};

    EXPECT_EQ(vec.getSize(), 3);

    EXPECT_EQ(vec.at(0), "apple");
    EXPECT_EQ(vec.at(1), "banana");
    EXPECT_EQ(vec.at(2), "strawberry");
}

TYPED_TEST(AssignmentTest, VectorAssignment_Num) 
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};

    Vector<TypeParam> resVec;

    resVec = vec;

    EXPECT_EQ(resVec.getSize(), 3);

    ConstIterator<TypeParam> vecIt = vec.cbegin();
    ConstIterator<TypeParam> resVecIt = resVec.cbegin();

    for (; vecIt; ++vecIt, ++resVecIt)
        EXPECT_EQ(*vecIt, *resVecIt);
}

TEST(AssignmentTest, VectorAssignment_SameType) 
{
    Vector<double> vec = {6.7, 6.7, 6.7};

    Vector<int> resVec;

    resVec = vec;

    EXPECT_EQ(resVec.getSize(), 3);

    ConstIterator<double> vecIt = vec.cbegin();
    ConstIterator<int> resVecIt = resVec.cbegin();

    for (; vecIt; ++vecIt, ++resVecIt)
        EXPECT_EQ(*resVecIt, 6);
}

TEST(AssignmentTest, VectorAssignment_Str) 
{
    Vector<string> vec = {"apple", "banana", "strawberry"};
    Vector<string> resVec;
    resVec = vec;

    EXPECT_EQ(resVec.getSize(), 3);

    ConstIterator<string> vecIt = vec.cbegin();
    ConstIterator<string> resVecIt = resVec.cbegin();

    for (; vecIt; ++vecIt, ++resVecIt)
        EXPECT_EQ(*vecIt, *resVecIt);
}

TYPED_TEST(AssignmentTest, RValueAssignment_Num) 
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};

    Vector<TypeParam> resVec;
    resVec = move(vec);

    EXPECT_EQ(vec.getSize(), 0);
    EXPECT_EQ(resVec.getSize(), 3);

    ConstIterator<TypeParam> resVecIt = resVec.cbegin();

    for (TypeParam i = TypeParam(1); resVecIt; ++resVecIt, ++i)
        EXPECT_EQ(*resVecIt, i);
}

TEST(AssignmentTest, RValueAssignment_Str) 
{
    Vector<string> vec = {"apple", "banana", "strawberry"};
    Vector<string> resVec;
    resVec = move(vec);

    EXPECT_EQ(vec.getSize(), 0);
    EXPECT_EQ(vec.isEmpty(), true);
    EXPECT_EQ(resVec.getSize(), 3);

    EXPECT_EQ(resVec.at(0), "apple");
    EXPECT_EQ(resVec.at(1), "banana");
    EXPECT_EQ(resVec.at(2), "strawberry");
}

#endif
