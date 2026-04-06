#ifndef TEST_BINARY_HPP
#define TEST_BINARY_HPP

#include <gtest/gtest.h>

#include "vector.h"

using namespace std;

template <typename T>
class BinaryTest : public ::testing::Test {};

using TestTypeBinary = ::testing::Types<int, double>;

TYPED_TEST_SUITE(BinaryTest, TestTypeBinary);

TYPED_TEST(BinaryTest, vecSum_SameType)
{
    Vector<TypeParam> vec1 = {TypeParam(1), TypeParam(2), TypeParam(3)};
    Vector<TypeParam> vec2 = {TypeParam(4), TypeParam(5), TypeParam(6)};
    Vector<TypeParam> expected = {TypeParam(5), TypeParam(7), TypeParam(9)};

    Vector<TypeParam> result1 = vec1.vecSum(vec2);
    Vector<TypeParam> result2 = vec1 + vec2;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TEST(BinaryTest, vecSum_DifferentTypes)
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<double> vec2 = {1.5, 2.5, 3.5};
    Vector<double> expected = {2.5, 4.5, 6.5};

    auto result1 = vec1.vecSum(vec2);
    auto result2 = vec1 + vec2;

    ConstIterator<double> it1 = result1.cbegin();
    ConstIterator<double> it3 = result2.cbegin();
    ConstIterator<double> it2 = expected.cbegin();

    for (; it1; ++it1, ++it2, ++it3)
    {
        EXPECT_EQ(*it1, *it2);
        EXPECT_EQ(*it3, *it2);
    }
}

TYPED_TEST(BinaryTest, vecSum_DifferentSizes)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5};

    EXPECT_THROW(vec1.vecSum(vec2), NotEqualSizesException);
    EXPECT_THROW(vec1 + vec2, NotEqualSizesException);
}

TYPED_TEST(BinaryTest, vecSum_EmptyVector)
{
    Vector<TypeParam> vec1;
    Vector<TypeParam> vec2 = {1, 2, 3};

    EXPECT_THROW(vec1.vecSum(vec2), NotEqualSizesException);
    EXPECT_THROW(vec2.vecSum(vec1), NotEqualSizesException);
    EXPECT_THROW(vec1 + vec2, NotEqualSizesException);
}

TYPED_TEST(BinaryTest, byNumSum_SameType)
{
    Vector<TypeParam> vec = {1, 2, 3};
    TypeParam num = 5;
    Vector<TypeParam> expected = {6, 7, 8};

    auto result1 = vec.byNumSum(num);
    auto result2 = vec + num;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TEST(BinaryTest, byNumSum_DifferentTypes)
{
    Vector<double> vec = {1, 2, 3};
    double num = 1.5;
    Vector<double> expected = {2.5, 3.5, 4.5};

    auto result1 = vec.byNumSum(num);
    auto result2 = vec + num;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TYPED_TEST(BinaryTest, eqVecSum_SameType)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5, 6};
    Vector<TypeParam> expected = {5, 7, 9};

    Vector<TypeParam> result1;
    result1 = vec1;
    result1.eqVecSum(vec2);

    Vector<TypeParam> result2 = {1, 2, 3};
    result2 += vec2;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TEST(BinaryTest, eqVecSum_DifferentTypes)
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<double> vec2 = {1.5, 2.5, 3.5};
    Vector<double> expected = {2.5, 4.5, 6.5};

    Vector<double> result;
    result = vec2;
    result.eqVecSum(vec1);

    ConstIterator<double> it1 = result.cbegin();
    ConstIterator<double> it2 = expected.cbegin();

    for (; it1; ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

TYPED_TEST(BinaryTest, eqVecSum_DifferentSizes)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5};

    EXPECT_THROW(vec1.eqVecSum(vec2), NotEqualSizesException);
    EXPECT_THROW(vec1 += vec2, NotEqualSizesException);
}

TYPED_TEST(BinaryTest, eqByNumSum_SameType)
{
    Vector<TypeParam> vec = {1, 2, 3};
    TypeParam num = 5;
    Vector<TypeParam> expected = {6, 7, 8};

    Vector<TypeParam> result1;
    result1 = vec;

    result1.eqByNumSum(num);

    Vector<TypeParam> result2 = {1, 2, 3};
    result2 += num;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}


TYPED_TEST(BinaryTest, vecDiff_SameType)
{
    Vector<TypeParam> vec1 = {5, 7, 9};
    Vector<TypeParam> vec2 = {4, 5, 6};
    Vector<TypeParam> expected = {1, 2, 3};

    auto result1 = vec1.vecDiff(vec2);
    auto result2 = vec1 - vec2;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TYPED_TEST(BinaryTest, vecDiff_DifferentSizes)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5};

    EXPECT_THROW(vec1.vecDiff(vec2), NotEqualSizesException);
    EXPECT_THROW(vec1 - vec2, NotEqualSizesException);
}


TYPED_TEST(BinaryTest, byNumDiff_SameType)
{
    Vector<TypeParam> vec = {6, 7, 8};
    TypeParam num = 5;
    Vector<TypeParam> expected = {1, 2, 3};

    auto result1 = vec.byNumDiff(num);
    auto result2 = vec - num;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}


TYPED_TEST(BinaryTest, vecProd_SameType)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5, 6};
    Vector<TypeParam> expected = {4, 10, 18};

    auto result1 = vec1.vecProd(vec2);
    auto result2 = vec1 * vec2;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}


TYPED_TEST(BinaryTest, byNumProd_SameType)
{
    Vector<TypeParam> vec = {1, 2, 3};
    TypeParam num = 5;
    Vector<TypeParam> expected = {5, 10, 15};

    auto result1 = vec.byNumProd(num);
    auto result2 = vec * num;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}


TYPED_TEST(BinaryTest, vecQuot_SameType)
{
    Vector<TypeParam> vec1 = {4, 10, 18};
    Vector<TypeParam> vec2 = {4, 5, 6};
    Vector<TypeParam> expected = {1, 2, 3};

    auto result1 = vec1.vecQuot(vec2);
    auto result2 = vec1 / vec2;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TYPED_TEST(BinaryTest, vecQuot_DivisionByZero)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {0, 1, 2};

    EXPECT_THROW(vec1.vecQuot(vec2), DivisionByZeroException);
    EXPECT_THROW(vec1 / vec2, DivisionByZeroException);
}


TYPED_TEST(BinaryTest, byNumQuot_SameType)
{
    Vector<TypeParam> vec = {4, 10, 18};
    TypeParam num = 2;
    Vector<TypeParam> expected = {2, 5, 9};

    auto result1 = vec.byNumQuot(num);
    auto result2 = vec / num;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TYPED_TEST(BinaryTest, byNumQuot_DivisionByZero)
{
    Vector<TypeParam> vec = {1, 2, 3};
    TypeParam num = 0;

    EXPECT_THROW(vec.byNumQuot(num), DivisionByZeroException);
    EXPECT_THROW(vec / num, DivisionByZeroException);
}


TYPED_TEST(BinaryTest, eqVecProd_SameType)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5, 6};
    Vector<TypeParam> expected = {4, 10, 18};

    Vector<TypeParam> result;
    result = vec1;
    result.eqVecProd(vec2);

    EXPECT_TRUE(expected == result);
}


TYPED_TEST(BinaryTest, eqByNumProd_SameType)
{
    Vector<TypeParam> vec = {1, 2, 3};
    TypeParam num = 5;
    Vector<TypeParam> expected = {5, 10, 15};

    Vector<TypeParam> result;
    result = vec;
    result.eqByNumProd(num);

    EXPECT_TRUE(expected == result);
}


TYPED_TEST(BinaryTest, eqVecQuot_SameType)
{
    Vector<TypeParam> vec1 = {4, 10, 18};
    Vector<TypeParam> vec2 = {4, 5, 6};
    Vector<TypeParam> expected = {1, 2, 3};

    Vector<TypeParam> result;
    result = vec1;
    result.eqVecQuot(vec2);

    EXPECT_TRUE(expected == result);
}


TEST(BinaryTest, neg)
{
    Vector<int> vec = {1, -2, 3};
    Vector<int> expected = {-1, 2, -3};

    auto result1 = vec.neg();
    auto result2 = -vec;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}


TYPED_TEST(BinaryTest, scalarProd_SameType)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5, 6};
    TypeParam expected = 1*4 + 2*5 + 3*6;

    auto result1 = vec1.scalarProd(vec2);
    auto result2 = vec1 & vec2;

    EXPECT_EQ(expected, result1);
    EXPECT_EQ(expected, result2);
}


TYPED_TEST(BinaryTest, vectorProd_3D)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {4, 5, 6};
    Vector<TypeParam> expected = {
        2*6 - 3*5,
        3*4 - 1*6,
        1*5 - 2*4
    };

    auto result1 = vec1.vectorProd(vec2);
    auto result2 = vec1 ^ vec2;

    EXPECT_TRUE(expected == result1);
    EXPECT_TRUE(expected == result2);
}

TYPED_TEST(BinaryTest, vectorProd_Not3D)
{
    Vector<TypeParam> vec1 = {1, 2};
    Vector<TypeParam> vec2 = {3, 4};

    EXPECT_THROW(vec1.vectorProd(vec2), Not3DException);
    EXPECT_THROW(vec1 ^ vec2, Not3DException);
}


TYPED_TEST(BinaryTest, angle)
{
    Vector<TypeParam> vec1 = {1, 0, 0};
    Vector<TypeParam> vec2 = {0, 1, 0};

    double angle = vec1.angle(vec2);
    double expected = M_PI / 2;

    EXPECT_NEAR(angle, expected, 1e-6);
}


TYPED_TEST(BinaryTest, isCollinear_True)
{
    Vector<double> vec1 = {1, 2, 3};
    Vector<double> vec2 = {2, 4, 6};

    EXPECT_TRUE(vec1.isCollinear(vec2));
}

TYPED_TEST(BinaryTest, isCollinear_False)
{
    Vector<TypeParam> vec1 = {1, 0, 0};
    Vector<TypeParam> vec2 = {0, 1, 0};

    EXPECT_FALSE(vec1.isCollinear(vec2));
}


TYPED_TEST(BinaryTest, isOrthogonal_True)
{
    Vector<TypeParam> vec1 = {1, 0, 0};
    Vector<TypeParam> vec2 = {0, 1, 0};

    EXPECT_TRUE(vec1.isOrthogonal(vec2));
}

TYPED_TEST(BinaryTest, isOrthogonal_False)
{
    Vector<TypeParam> vec1 = {1, 2, 3};
    Vector<TypeParam> vec2 = {2, 4, 6};

    EXPECT_FALSE(vec1.isOrthogonal(vec2));
}

TYPED_TEST(BinaryTest, isZero_True)
{
    Vector<TypeParam> vec = {0, 0, 0};
    EXPECT_TRUE(vec.isZero());
}

TYPED_TEST(BinaryTest, isZero_False)
{
    Vector<TypeParam> vec = {1, 2, 3};
    EXPECT_FALSE(vec.isZero());
}

#endif
