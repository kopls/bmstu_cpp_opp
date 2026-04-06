#ifndef TEST_ITERATOR_HPP
#define TEST_ITERATOR_HPP

#include <gtest/gtest.h>
#include <algorithm>

#include "vector.h"

using namespace std;

template <typename T>
class IteratorTest : public ::testing::Test {};

using TestType = ::testing::Types<int, double, size_t>;

TYPED_TEST_SUITE(IteratorTest, TestType);

// ========== ТЕСТЫ ДЛЯ begin() И end() ==========

TYPED_TEST(IteratorTest, BeginEnd_IterateForward)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    TypeParam expected = TypeParam(1);
    for (auto it = vec.begin(); it != vec.end(); ++it, ++expected)
        EXPECT_EQ(*it, expected);
}

TYPED_TEST(IteratorTest, BeginEnd_EmptyVector)
{
    Vector<TypeParam> vec;
    
    EXPECT_EQ(vec.begin(), vec.end());
}

// ========== ТЕСТЫ ДЛЯ cbegin() И cend() ==========

TYPED_TEST(IteratorTest, ConstBeginEnd_IterateForward)
{
    const Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    TypeParam expected = TypeParam(1);
    for (auto it = vec.cbegin(); it != vec.cend(); ++it, ++expected)
        EXPECT_EQ(*it, expected);
}

// ========== ТЕСТЫ ДЛЯ rbegin() И rend() ==========

TYPED_TEST(IteratorTest, ReverseBeginEnd_IterateBackward)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    TypeParam expected = TypeParam(5);
    for (auto it = vec.rbegin(); it != vec.rend(); ++it, --expected)
        EXPECT_EQ(*it, expected);
}

TYPED_TEST(IteratorTest, ReverseBeginEnd_EmptyVector)
{
    Vector<TypeParam> vec;
    
    EXPECT_EQ(vec.rbegin(), vec.rend());
}

// ========== ТЕСТЫ ДЛЯ crbegin() И crend() ==========

TYPED_TEST(IteratorTest, ConstReverseBeginEnd_IterateBackward)
{
    const Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    TypeParam expected = TypeParam(5);
    for (auto it = vec.crbegin(); it != vec.crend(); ++it, --expected)
        EXPECT_EQ(*it, expected);
}

// ========== ТЕСТЫ ДЛЯ ОПЕРАТОРОВ ИТЕРАТОРОВ ==========

TYPED_TEST(IteratorTest, Iterator_Subscript)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    auto it = vec.begin();
    
    EXPECT_EQ(it[0], TypeParam(1));
    EXPECT_EQ(it[2], TypeParam(3));
    EXPECT_EQ(it[4], TypeParam(5));
}

TYPED_TEST(IteratorTest, Iterator_Comparison)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
    auto first = vec.begin();
    auto second = vec.begin();
    ++second;
    auto last = vec.end();

    std::cout << "first points to: " << std::addressof(*first) << std::endl;
    std::cout << "second points to: " << std::addressof(*second) << std::endl;
    
    EXPECT_TRUE(first < second);
    EXPECT_TRUE(second > first);
    EXPECT_TRUE(first <= first);
    EXPECT_TRUE(first >= first);
    EXPECT_TRUE(first == first);
    EXPECT_TRUE(last == last);
    EXPECT_TRUE(first != second);
    EXPECT_TRUE(first < last);
}

TYPED_TEST(IteratorTest, Iterator_PrePostIncrement)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
    auto it = vec.begin();
    
    auto old = it++;
    EXPECT_EQ(*old, TypeParam(1));
    EXPECT_EQ(*it, TypeParam(2));
    
    ++it;
    EXPECT_EQ(*it, TypeParam(3));
}

TYPED_TEST(IteratorTest, Iterator_PrePostDecrement)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
    auto it = vec.end();
    --it;
    
    EXPECT_EQ(*it, TypeParam(3));
    
    --it;
    EXPECT_EQ(*it, TypeParam(2));
}

// ========== ТЕСТЫ ДЛЯ REVERSE ИТЕРАТОРА ==========

TYPED_TEST(IteratorTest, ReverseIterator_Increment)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    auto it = vec.rbegin();
    
    EXPECT_EQ(*it, TypeParam(5));
    ++it;
    EXPECT_EQ(*it, TypeParam(4));
    ++it;
    EXPECT_EQ(*it, TypeParam(3));
    ++it;
    EXPECT_EQ(*it, TypeParam(2));
    ++it;
    EXPECT_EQ(*it, TypeParam(1));
}

TYPED_TEST(IteratorTest, ReverseIterator_Decrement)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    auto it = vec.rend();
    --it;
    
    EXPECT_EQ(*it, TypeParam(1));
    --it;
    EXPECT_EQ(*it, TypeParam(2));
    --it;
    EXPECT_EQ(*it, TypeParam(3));
    --it;
    EXPECT_EQ(*it, TypeParam(4));
    --it;
    EXPECT_EQ(*it, TypeParam(5));
}

TYPED_TEST(IteratorTest, ReverseIterator_Comparison)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
    auto first = vec.rbegin();
    auto second = vec.rbegin();
    ++second;
    
    EXPECT_TRUE(first != second);
    EXPECT_TRUE(first == first);
}

// ========== ТЕСТЫ ДЛЯ СТАНДАРТНЫХ АЛГОРИТМОВ ==========

TYPED_TEST(IteratorTest, Algorithm_Sort)
{
    Vector<TypeParam> vec = {TypeParam(5), TypeParam(2), TypeParam(4), TypeParam(1), TypeParam(3)};
    
    std::sort(vec.begin(), vec.end());
    
    EXPECT_EQ(vec[0], TypeParam(1));
    EXPECT_EQ(vec[1], TypeParam(2));
    EXPECT_EQ(vec[2], TypeParam(3));
    EXPECT_EQ(vec[3], TypeParam(4));
    EXPECT_EQ(vec[4], TypeParam(5));
}

TYPED_TEST(IteratorTest, Algorithm_Reverse)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    std::reverse(vec.begin(), vec.end());
    
    EXPECT_EQ(vec[0], TypeParam(5));
    EXPECT_EQ(vec[1], TypeParam(4));
    EXPECT_EQ(vec[2], TypeParam(3));
    EXPECT_EQ(vec[3], TypeParam(2));
    EXPECT_EQ(vec[4], TypeParam(1));
}

TYPED_TEST(IteratorTest, Algorithm_Find)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    auto it = std::find(vec.begin(), vec.end(), TypeParam(3));
    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, TypeParam(3));
    
    it = std::find(vec.begin(), vec.end(), TypeParam(99));
    EXPECT_EQ(it, vec.end());
}

TYPED_TEST(IteratorTest, Algorithm_ForEach)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3)};
    
    TypeParam sum = TypeParam(0);
    std::for_each(vec.begin(), vec.end(), [&sum](TypeParam x) { sum += x; });
    
    EXPECT_EQ(sum, TypeParam(6));
}

TYPED_TEST(IteratorTest, RangeBasedFor)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    TypeParam expected = TypeParam(1);
    for (const auto& val : vec)
    {
        EXPECT_EQ(val, expected);
        ++expected;
    }
}

TYPED_TEST(IteratorTest, RangeBasedFor_Reverse)
{
    Vector<TypeParam> vec = {TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4), TypeParam(5)};
    
    TypeParam expected = TypeParam(5);
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
        EXPECT_EQ(*it, expected);
        --expected;
    }
}

// ========== ТЕСТЫ ДЛЯ STRING ==========

TEST(IteratorTestString, StringIteration)
{
    Vector<string> vec = {"apple", "banana", "cherry"};
    
    auto it = vec.begin();
    EXPECT_EQ(*it, "apple"); ++it;
    EXPECT_EQ(*it, "banana"); ++it;
    EXPECT_EQ(*it, "cherry");
}

TEST(IteratorTestString, StringReverseIteration)
{
    Vector<string> vec = {"apple", "banana", "cherry"};
    
    auto it = vec.rbegin();
    EXPECT_EQ(*it, "cherry"); ++it;
    EXPECT_EQ(*it, "banana"); ++it;
    EXPECT_EQ(*it, "apple");
}

#endif
