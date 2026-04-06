#ifndef TEST_ASSIGMENT_HPP
#define TEST_ASSIGMENT_HPP

#include <gtest/gtest.h>
#include <list>

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

TEST(RangeConstructorTest, FromVector)
{
    std::vector<int> source = {1, 2, 3, 4, 5};
    Vector<int> vec(source);

    EXPECT_EQ(vec.getSize(), 5);

    ConstIterator<int> it = vec.cbegin();
    for (int i = 1; i <= 5; ++i, ++it)
        EXPECT_EQ(*it, i);
}

TEST(RangeConstructorTest, FromList)
{
    std::list<double> source = {1.5, 2.5, 3.5, 4.5};
    Vector<int> vec(source);  // double -> int конвертация

    EXPECT_EQ(vec.getSize(), 4);

    ConstIterator<int> it = vec.cbegin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3); ++it;
    EXPECT_EQ(*it, 4);
}

TEST(RangeConstructorTest, FromArray)
{
    std::array<char, 5> source = {'a', 'b', 'c', 'd', 'e'};
    Vector<char> vec(source);

    EXPECT_EQ(vec.getSize(), 5);

    ConstIterator<char> it = vec.cbegin();
    EXPECT_EQ(*it, 'a'); ++it;
    EXPECT_EQ(*it, 'b'); ++it;
    EXPECT_EQ(*it, 'c'); ++it;
    EXPECT_EQ(*it, 'd'); ++it;
    EXPECT_EQ(*it, 'e');
}

TEST(RangeConstructorTest, FromString)
{
    std::string source = "hello";
    Vector<char> vec(source);

    EXPECT_EQ(vec.getSize(), 5);

    ConstIterator<char> it = vec.cbegin();
    EXPECT_EQ(*it, 'h'); ++it;
    EXPECT_EQ(*it, 'e'); ++it;
    EXPECT_EQ(*it, 'l'); ++it;
    EXPECT_EQ(*it, 'l'); ++it;
    EXPECT_EQ(*it, 'o');
}

TEST(RangeConstructorTest, FromInitializerList)
{
    Vector<int> vec = {1, 2, 3, 4, 5};

    EXPECT_EQ(vec.getSize(), 5);

    ConstIterator<int> it = vec.cbegin();
    for (int i = 1; i <= 5; ++i, ++it)
        EXPECT_EQ(*it, i);
}

TEST(RangeConstructorTest, FromEmptyVector)
{
    std::vector<int> source;
    Vector<int> vec(source);

    EXPECT_EQ(vec.getSize(), 0);
    EXPECT_TRUE(vec.isEmpty());
}

TEST(RangeConstructorTest, FromVectorOfDifferentType)
{
    std::vector<double> source = {1.1, 2.2, 3.3, 4.4};
    Vector<int> vec(source);  // конвертация double -> int

    EXPECT_EQ(vec.getSize(), 4);

    ConstIterator<int> it = vec.cbegin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3); ++it;
    EXPECT_EQ(*it, 4);
}

TEST(RangeConstructorTest, FromStringToIntVector)
{
    std::string source = "12345";
    Vector<int> vec(source);  // char -> int конвертация

    EXPECT_EQ(vec.getSize(), 5);

    ConstIterator<int> it = vec.cbegin();
    EXPECT_EQ(*it, '1'); ++it;
    EXPECT_EQ(*it, '2'); ++it;
    EXPECT_EQ(*it, '3'); ++it;
    EXPECT_EQ(*it, '4'); ++it;
    EXPECT_EQ(*it, '5');
}

TEST(RangeConstructorTest, FromStdArray)
{
    std::array<int, 3> source = {10, 20, 30};
    Vector<int> vec(source);

    EXPECT_EQ(vec.getSize(), 3);

    ConstIterator<int> it = vec.cbegin();
    EXPECT_EQ(*it, 10); ++it;
    EXPECT_EQ(*it, 20); ++it;
    EXPECT_EQ(*it, 30);
}

TEST(RangeConstructorTest, MultipleVectorsFromSameSource)
{
    std::vector<int> source = {1, 2, 3};

    Vector<int> vec1(source);
    Vector<int> vec2(source);
    Vector<int> vec3(source);

    EXPECT_EQ(vec1.getSize(), 3);
    EXPECT_EQ(vec2.getSize(), 3);
    EXPECT_EQ(vec3.getSize(), 3);

    EXPECT_EQ(vec1[0], vec2[0]);
    EXPECT_EQ(vec1[1], vec2[1]);
    EXPECT_EQ(vec1[2], vec2[2]);
}

#endif
