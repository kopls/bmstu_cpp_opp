#ifndef TEST_CONSTRUCTOR_HPP
#define TEST_CONSTRUCTOR_HPP

#include <gtest/gtest.h>

#include "vector.h"

using namespace std;

template <typename T>
class ConstructorTest : public ::testing::Test {};

using TestType = ::testing::Types<int, double, size_t>;

TYPED_TEST_SUITE(ConstructorTest, TestType);

TYPED_TEST(ConstructorTest, DefaultConstructor_Num) 
{
    Vector<TypeParam> v;

    EXPECT_EQ(v.isEmpty(), true);

    EXPECT_EQ(v.getSize(), 0);
}

TEST(ConstructorTest, DefaultConstructor_Str)
{
    Vector<string> v;

    EXPECT_EQ(v.isEmpty(), true);

    EXPECT_EQ(v.getSize(), 0);
}

TYPED_TEST(ConstructorTest, SizeValueConstructor_Num) 
{
    Vector<TypeParam> v(5);

    EXPECT_EQ(v.isEmpty(), false);

    EXPECT_EQ(v.getSize(), 5);
}

TEST(ConstructorTest, SizeValueConstructor_Str)
{
    Vector<string> v(5);

    EXPECT_EQ(v.isEmpty(), false);

    EXPECT_EQ(v.getSize(), 5);
}

TYPED_TEST(ConstructorTest, CopyConstructor_Num) 
{
    Vector<TypeParam> vec{TypeParam(1), TypeParam(2), TypeParam(3),
                          TypeParam(4), TypeParam(5)};

    Vector<TypeParam> copyV(vec);

    EXPECT_EQ(vec.getSize(), copyV.getSize());

    ConstIterator<TypeParam> vecIt = vec.cbegin();
    ConstIterator<TypeParam> copyIt = copyV.cbegin();

    for (; copyIt; ++copyIt, ++vecIt)
        EXPECT_EQ(*vecIt, *copyIt);

    copyV.at(0) = TypeParam(10);
    EXPECT_NE(copyV.at(0), vec.at(0));
}

TEST(ConstructorTest, CopyConstructor_Str) 
{
    Vector<string> vec{"apple", "banana", "pineapple"};

    Vector<string> copyV(vec);

    EXPECT_EQ(vec.getSize(), copyV.getSize());

    ConstIterator<string> vecIt = vec.cbegin();
    ConstIterator<string> copyIt = copyV.cbegin();

    for (; copyIt; ++copyIt, ++vecIt)
        EXPECT_EQ(*vecIt, *copyIt);

    copyV.at(0) = "cherry";
    EXPECT_NE(copyV.at(0), vec.at(0));
}

TYPED_TEST(ConstructorTest, FillerConstructor_Num) 
{
    size_t size = 5;
    int filler = 67;

    Vector<TypeParam> vec(size, TypeParam(filler));


    EXPECT_EQ(vec.getSize(), size);

    ConstIterator<TypeParam> vecIt = vec.cbegin();

    for (; vecIt; ++vecIt)
        EXPECT_EQ(*vecIt, filler);
}

TEST(ConstructorTest, FillerConstructor_Str) 
{
    size_t size = 5;
    string filler = "test";

    Vector<string> vec(size, filler);

    EXPECT_EQ(vec.getSize(), size);

    ConstIterator<string> vecIt = vec.cbegin();

    for (; vecIt; ++vecIt)
        EXPECT_EQ(*vecIt, filler);
}

TYPED_TEST(ConstructorTest, ArrConstructor_Num) 
{
    size_t size = 5;

    const TypeParam arr[] = {TypeParam(1), TypeParam(2), TypeParam(3),
                          TypeParam(4), TypeParam(5)};

    Vector<TypeParam> vec(size, arr); 

    EXPECT_EQ(vec.getSize(), size);

    ConstIterator<TypeParam> vecIt = vec.cbegin();

    for (size_t i = 0; vecIt; ++vecIt, ++i)
        EXPECT_EQ(*vecIt, arr[i]);
}

TEST(ConstructorTest, ArrConstructor_Str) 
{
    size_t size = 3;

    const string arr[] = {"Artyom", "Svyat", "Daniil"};

    Vector<string> vec(size, arr); 

    EXPECT_EQ(vec.getSize(), size);

    ConstIterator<string> vecIt = vec.cbegin();

    for (size_t i = 0; vecIt; ++vecIt, ++i)
        EXPECT_EQ(*vecIt, arr[i]);
}

TYPED_TEST(ConstructorTest, Init_ListConstructor_Num) 
{
    Vector<TypeParam> vec{TypeParam(1), TypeParam(2), TypeParam(3)};

    EXPECT_EQ(vec.getSize(), 3);

    ConstIterator<TypeParam> vecIt = vec.cbegin();

    for (TypeParam i = TypeParam(1); vecIt; ++vecIt, ++i)
        EXPECT_EQ(*vecIt, i);
}

TEST(ConstructorTest, Init_ListConstructor_Str) 
{
    Vector<string> vec{"apple", "banana", "strawberry"};

    EXPECT_EQ(vec.getSize(), 3);

    ConstIterator<string> vecIt = vec.cbegin();
    
    EXPECT_EQ(vec.at(0), "apple");
    EXPECT_EQ(vec.at(1), "banana");
    EXPECT_EQ(vec.at(2), "strawberry");
}

TYPED_TEST(ConstructorTest, MoveConstructor_Num) 
{
    Vector<TypeParam> rvalueVec{TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec(move(rvalueVec));

    EXPECT_EQ(vec.getSize(), 3);

    ConstIterator<TypeParam> vecIt = vec.cbegin();

    for (TypeParam i = TypeParam(1); vecIt; ++vecIt, ++i)
        EXPECT_EQ(*vecIt, i);

    rvalueVec.at(0) = TypeParam(67);

    EXPECT_NE(vec.at(0), rvalueVec.at(0));
}

TEST(ConstructorTest, MoveConstructor_Str) 
{
    Vector<string> rvalueVec{"Masha", "Sonya", "Artyom"};
    Vector<string> vec(move(rvalueVec));

    EXPECT_EQ(vec.getSize(), 3);

    ConstIterator<string> vecIt = vec.cbegin();

    EXPECT_EQ(vec.at(0), "Masha");
    EXPECT_EQ(vec.at(1), "Sonya");
    EXPECT_EQ(vec.at(2), "Artyom");

    rvalueVec.at(0) = "GUGUGAGA";

    EXPECT_NE(vec.at(0), rvalueVec.at(0));
}

TYPED_TEST(ConstructorTest, IteratorConstructor_Num) 
{
    Vector<TypeParam> vec{TypeParam(1), TypeParam(2), TypeParam(3)};
    ConstIterator<TypeParam> begin = vec.cbegin();
    ConstIterator<TypeParam> end = vec.cend();
    Vector<TypeParam> resVec(begin, end);

    EXPECT_EQ(resVec.getSize(), 3);

    ConstIterator<TypeParam> vecIt = vec.cbegin();
    ConstIterator<TypeParam> resVecIt = resVec.cbegin();

    for (; vecIt; ++vecIt, ++resVecIt)
        EXPECT_EQ(*vecIt, *resVecIt);

    resVec.at(0) = TypeParam(67);

    EXPECT_NE(vec.at(0), resVec.at(0));
}

TEST(ConstructorTest, IteratorConstructor_String) 
{
    Vector<string> vec{"raspberry", "blueberry", "strawberry"};
    ConstIterator<string> begin = vec.cbegin();
    ConstIterator<string> end = vec.cend();
    Vector<string> resVec(begin, end);

    EXPECT_EQ(resVec.getSize(), 3);

    ConstIterator<string> vecIt = vec.cbegin();
    ConstIterator<string> resVecIt = resVec.cbegin();

    for (; vecIt; ++vecIt, ++resVecIt)
        EXPECT_EQ(*vecIt, *resVecIt);

    resVec.at(0) = "blackberry";

    EXPECT_NE(vec.at(0), resVec.at(0));
}

#endif
