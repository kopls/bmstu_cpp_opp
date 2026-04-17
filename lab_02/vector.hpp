#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <limits>
#include <algorithm>
#include <numeric>
#include <ranges>

#include "vector.h"
#include "exceptions.h"

#define EPS __DBL_EPSILON__

// Iterators
template<VectorElement Type>
typename Vector<Type>::iterator Vector<Type>::begin() noexcept
{
    return iterator(data, size, 0);
}

template<VectorElement Type>
typename Vector<Type>::iterator Vector<Type>::end() noexcept
{
    return iterator(data, size, size);
}

template<VectorElement Type>
typename Vector<Type>::const_iterator Vector<Type>::begin() const noexcept
{
    return const_iterator(data, size, 0);
}

template<VectorElement Type>
typename Vector<Type>::const_iterator Vector<Type>::end() const noexcept
{
    return const_iterator(data, size, size);
}

template<VectorElement Type>
typename Vector<Type>::const_iterator Vector<Type>::cbegin() const noexcept
{
    return const_iterator(data, size, 0);
}

template<VectorElement Type>
typename Vector<Type>::const_iterator Vector<Type>::cend() const noexcept
{
    return const_iterator(data, size, size);
}

template<VectorElement Type>
typename Vector<Type>::reverse_iterator Vector<Type>::rbegin() noexcept
{
    return reverse_iterator(data, size, size - 1);
}

template<VectorElement Type>
typename Vector<Type>::reverse_iterator Vector<Type>::rend() noexcept
{
    return reverse_iterator(data, size, -1);
}

template<VectorElement Type>
typename Vector<Type>::const_reverse_iterator Vector<Type>::rbegin() const noexcept
{
    return const_reverse_iterator(data, size, size - 1);
}

template<VectorElement Type>
typename Vector<Type>::const_reverse_iterator Vector<Type>::rend() const noexcept
{
    return const_reverse_iterator(data, size, -1);
}

template<VectorElement Type>
typename Vector<Type>::const_reverse_iterator Vector<Type>::crbegin() const noexcept
{
    return const_reverse_iterator(data, size, size - 1);
}

template<VectorElement Type>
typename Vector<Type>::const_reverse_iterator Vector<Type>::crend() const noexcept
{
    return const_reverse_iterator(data, size, -1);
}

// Constructors
template<VectorElement Type>
Vector<Type>::Vector(typename Vector<Type>::size_type sizeValue)
{
    allocate(sizeValue);
    size = sizeValue;
}

template<VectorElement Type>
Vector<Type>::Vector(typename Vector<Type>::size_type sizeValue, typename Vector<Type>::const_reference filler) 
{
    allocate(sizeValue);
    size = sizeValue;
    std::ranges::fill(*this, filler);
}

template<VectorElement Type>
template <ConvertibleTo<Type> Type2>
Vector<Type>::Vector(typename Vector<Type>::size_type sizeValue, const Type2 &filler)
{
    allocate(sizeValue);
    size = sizeValue;
    std::ranges::fill(*this, static_cast<Type>(filler));
}

template<VectorElement Type>
Vector<Type>::Vector(typename Vector<Type>::size_type sizeValue, typename Vector<Type>::const_pointer arr) 
{
    allocate(sizeValue);
    size = sizeValue;
    std::ranges::copy(arr, arr + size, begin());
}

template<VectorElement Type>
template <ConvertibleTo<Type> Type2>
Vector<Type>::Vector(typename Vector<Type>::size_type sizeValue, const Type2 *arr)
{
    allocate(sizeValue);
    size = sizeValue;
    std::ranges::transform(arr, arr + size, begin(),
                          [](const Type2& val) { return static_cast<Type>(val); });
}

template<VectorElement Type>
Vector<Type>::Vector(initializer_list<typename Vector<Type>::value_type> elements)
{
    allocate(elements.size());
    size = elements.size();
    std::ranges::copy(elements, begin());
}

template<VectorElement Type>
template <ConvertibleTo<Type> Type2>
Vector<Type>::Vector(initializer_list<Type2> elements)
{
    allocate(elements.size());
    size = elements.size();
    std::ranges::transform(elements, begin(),
                          [](const Type2& val) { return static_cast<Type>(val); });
}

template<VectorElement Type>
Vector<Type>::Vector(const Vector &vector) 
{
    allocate(vector.size);
    size = vector.size;
    std::ranges::copy(vector, begin());
}

template<VectorElement Type>
template <ConvertibleTo<Type> Type2>
Vector<Type>::Vector(const Vector<Type2> &vector)
{
    allocate(vector.getSize());
    size = vector.getSize();
    std::ranges::transform(vector, begin(),
                          [](const Type2& val) { return static_cast<Type>(val); });
}

template<VectorElement Type>
Vector<Type>::Vector(Vector &&vector) noexcept
{
    size = vector.size;
    data = vector.data;
    vector.data.reset();
    vector.size = 0;
}

template<VectorElement Type>
template<input_iterator Iter, sentinel_for<Iter> Sent>
requires ConvertibleTo<iter_value_t<Iter>, typename Vector<Type>::value_type>
Vector<Type>::Vector(const Iter& begin, const Sent& end)
{
    typename Vector<Type>::size_type len = std::distance(begin, end);
    allocate(len);
    size = len;
    std::ranges::copy(begin, end, this->begin());
}

template<VectorElement Type>
template<std::ranges::input_range Range>
requires ConvertibleTo<std::ranges::range_value_t<Range>, typename Vector<Type>::value_type>
Vector<Type>::Vector(Range&& range)
{
    size = std::ranges::size(range);
    allocate(size);
    std::ranges::copy(range, begin());
}

// Assigment
template<VectorElement Type>
Vector<Type> &Vector<Type>::operator=(const Vector &vector)
{
    allocate(vector.size);
    size = vector.size;
    std::ranges::copy(vector, begin());
    return *this;
}

template<VectorElement Type>
Vector<Type> &Vector<Type>::operator=(Vector &&vector) noexcept
{
    size = vector.size;
    data = vector.data;
    vector.data.reset();
    vector.size = 0;
    return *this;
}

template<VectorElement Type>
template<ConvertibleTo<Type> Type2>
Vector<Type> &Vector<Type>::operator=(const Vector<Type2> &vector)
{
    allocate(vector.getSize());
    size = vector.getSize();
    std::ranges::transform(vector, begin(),
                          [](const Type2& val) { return static_cast<Type>(val); });
    return *this;
}

template<VectorElement Type>
template<ConvertibleTo<Type> Type2>
Vector<Type> &Vector<Type>::operator=(initializer_list<Type2> elements)
{
    allocate(elements.size());
    size = elements.size();
    std::ranges::transform(elements, begin(),
                          [](const Type2& val) { return static_cast<Type>(val); });
    return *this;
}

// Comparison
template<VectorElement Type>
template<EqualityComparableWith<Type> Type2>
bool Vector<Type>::operator==(const Vector<Type2> &vector) const
{
    return isEqual(vector);
}

template<VectorElement Type>
template <EqualityComparableWith<Type> Type2>
bool Vector<Type>::isEqual(const Vector<Type2> &vector) const
{
    if (size != vector.getSize())
        return false;
    return std::ranges::equal(*this, vector);
}

template<VectorElement Type>
template <EqualityComparableWith<Type> Type2>
bool Vector<Type>::operator!=(const Vector<Type2> &vector) const
{
    return isNotEqual(vector);
}

template<VectorElement Type>
template <EqualityComparableWith<Type> Type2>
bool Vector<Type>::isNotEqual(const Vector<Type2> &vector) const
{
    return !(*this == vector);
}

// Methods, operators
template<VectorElement Type>
template<ConvertibleTo<double> U>
Type Vector<Type>::length() const
{
    zeroSizeCheck(__LINE__);
    
    auto square = [](const Type& x) { return x * x; };
    Type len = std::accumulate(cbegin(), cend(), Type(0),
                               [&square](Type acc, const Type& x) {
                                   return acc + square(x);
                               });
    return std::sqrt(len);
}

template<VectorElement Type>
template<ConvertibleTo<double> U>
Vector<Type> Vector<Type>::getUnit() const
{
    zeroSizeCheck(__LINE__);
    Vector<Type> res(size);
    Type len = length();
    std::ranges::transform(*this, res.begin(),
                          [len](const Type& val) { return val / len; });
    return res;
}

template<VectorElement Type>
typename Vector<Type>::reference Vector<Type>::at(typename Vector<Type>::size_type index)
{
    indexCheck(index, __LINE__);
    return data[index];
}

template<VectorElement Type>
typename Vector<Type>::reference Vector<Type>::operator[](typename Vector<Type>::size_type index)
{
    return at(index);
}

template<VectorElement Type>
typename Vector<Type>::const_reference Vector<Type>::at(typename Vector<Type>::size_type index) const
{
    indexCheck(index, __LINE__);
    return data[index];
}

template<VectorElement Type>
typename Vector<Type>::const_reference Vector<Type>::operator[](typename Vector<Type>::size_type index) const
{
    return at(index);
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
decltype(auto) Vector<Type>::vecSum(const Vector<Type2> &vector) const
{
    sizesCheck(vector, __LINE__);
    Vector<decltype(at(0) + vector.at(0))> res(size);

    for (size_t i = 0; i < size; ++i)
        res.at(i) = at(i) + vector.at(i);

    return res;
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
decltype(auto) Vector<Type>::operator+(const Vector<Type2> &vector) const
{
    return vecSum(vector);
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
decltype(auto) Vector<Type>::byNumSum(const Type2 &num) const
{
    Vector<decltype(at(0) + num)> res(size);
    std::ranges::transform(*this, res.begin(),
                          [&num](const Type& val) { return val + num; });
    return res;
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
decltype(auto) Vector<Type>::operator+(const Type2 &num) const
{
    return byNumSum(num);
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
Vector<Type> &Vector<Type>::eqVecSum(const Vector<Type2> &vector)
{
    sizesCheck(vector, __LINE__);

    for (size_t i = 0; i < size; ++i)
        at(i) += vector.at(i);

    return *this;
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
Vector<Type> &Vector<Type>::operator+=(const Vector<Type2> &vector)
{
    return eqVecSum(vector);
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
Vector<Type> &Vector<Type>::eqByNumSum(const Type2 &num)
{
    std::ranges::transform(*this, begin(),
                          [&num](const Type& val) { return val + num; });
    return *this;
}

template<VectorElement Type>
template <SupportSum<Type> Type2>
Vector<Type> &Vector<Type>::operator+=(const Type2 &num)
{
    return eqByNumSum(num);
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
decltype(auto) Vector<Type>::vecDiff(const Vector<Type2> &vector) const
{
    sizesCheck(vector, __LINE__);
    Vector<decltype(at(0) - vector.at(0))> res(size);

    for (size_t i = 0; i < size; ++i)
        res.at(i) = at(i) - vector.at(i);

    return res;
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
decltype(auto) Vector<Type>::operator-(const Vector<Type2> &vector) const
{
    return vecDiff(vector);
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
decltype(auto) Vector<Type>::byNumDiff(const Type2 &num) const
{
    Vector<decltype(at(0) - num)> res(size);
    std::ranges::transform(*this, res.begin(),
                          [&num](const Type& val) { return val - num; });
    return res;
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
decltype(auto) Vector<Type>::operator-(const Type2 &num) const
{
    return byNumDiff(num);
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
Vector<Type> &Vector<Type>::eqVecDiff(const Vector<Type2> &vector) 
{
    sizesCheck(vector, __LINE__);

    for (size_t i = 0; i < size; ++i)
        at(i) -= vector.at(i);

    return *this;
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
Vector<Type> &Vector<Type>::operator-=(const Vector<Type2> &vector) 
{
    return eqVecDiff(vector);
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
Vector<Type> &Vector<Type>::eqByNumDiff(const Type2 &num) 
{
    std::ranges::transform(*this, begin(),
                          [&num](const Type& val) { return val - num; });
    return *this;
}

template<VectorElement Type>
template <SupportSub<Type> Type2>
Vector<Type> &Vector<Type>::operator-=(const Type2 &num) 
{
    return eqByNumDiff(num);
}

template<VectorElement Type>
template<ConvertibleTo<double> U>
Vector<Type> Vector<Type>::neg() const
{
    Vector<Type> res(size);
    std::ranges::transform(*this, res.begin(), std::negate<>());
    return res;
}

template<VectorElement Type>
template<ConvertibleTo<double> U>
Vector<Type> Vector<Type>::operator-() const
{
    return neg();
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
decltype(auto) Vector<Type>::vecProd(const Vector<Type2> &vector) const 
{
    sizesCheck(vector, __LINE__);
    Vector<decltype(at(0) * vector.at(0))> res(size);

    for (size_t i = 0; i < size; ++i)
        res.at(i) = at(i) * vector.at(i);

    return res;
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
decltype(auto) Vector<Type>::operator*(const Vector<Type2> &vector) const 
{
    return vecProd(vector);
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
decltype(auto) Vector<Type>::byNumProd(const Type2 &num) const 
{
    Vector<decltype(at(0) * num)> res(size);
    std::ranges::transform(*this, res.begin(),
                          [&num](const Type& val) { return val * num; });
    return res;
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
decltype(auto) Vector<Type>::operator*(const Type2 &num) const 
{
    return byNumProd(num);
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
Vector<Type> &Vector<Type>::eqVecProd(const Vector<Type2> &vector) 
{
    sizesCheck(vector, __LINE__);

    for (size_t i = 0; i < size; ++i)
        at(i) *= vector.at(i);

    return *this;
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
Vector<Type> &Vector<Type>::operator*=(const Vector<Type2> &vector) 
{
    return eqVecProd(vector);
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
Vector<Type> &Vector<Type>::eqByNumProd(const Type2 &num) 
{
    std::ranges::transform(*this, begin(),
                          [&num](const Type& val) { return val * num; });
    return *this;
}

template<VectorElement Type>
template <SupportProd<Type> Type2>
Vector<Type> &Vector<Type>::operator*=(const Type2 &num) 
{
    return eqByNumProd(num);
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
decltype(auto) Vector<Type>::vecQuot(const Vector<Type2> &vector) const 
{
    sizesCheck(vector, __LINE__);
    divisionByZeroCheck(vector.at(0), __LINE__);
    Vector<decltype(at(0) / vector.at(0))> res(size);

    for (size_t i = 0; i < size; ++i)
    {
        divisionByZeroCheck(vector.at(i), __LINE__);
        res.at(i) = at(i) / vector.at(i);
    }

    return res;
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
decltype(auto) Vector<Type>::operator/(const Vector<Type2> &vector) const 
{
    return vecQuot(vector);
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
decltype(auto) Vector<Type>::byNumQuot(const Type2 &num) const 
{
    divisionByZeroCheck(num, __LINE__);
    Vector<decltype(at(0) / num)> res(size);
    std::ranges::transform(*this, res.begin(),
                          [&num](const Type& val) { return val / num; });
    return res;
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
decltype(auto) Vector<Type>::operator/(const Type2 &num) const 
{
    return byNumQuot(num);
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
Vector<Type> &Vector<Type>::eqVecQuot(const Vector<Type2> &vector) 
{
    sizesCheck(vector, __LINE__);

    for (size_t i = 0; i < size; ++i)
    {
        divisionByZeroCheck(vector.at(i), __LINE__);
        at(i) /= vector.at(i);
    }

    return *this;
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
Vector<Type> &Vector<Type>::operator/=(const Vector<Type2> &vector) 
{
    return eqVecQuot(vector);
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
Vector<Type> &Vector<Type>::eqByNumQuot(const Type2 &num) 
{
    divisionByZeroCheck(num, __LINE__);
    std::ranges::transform(*this, begin(),
                          [&num](const Type& val) { return val / num; });
    return *this;
}

template<VectorElement Type>
template <SupportQuot<Type> Type2>
Vector<Type> &Vector<Type>::operator/=(const Type2 &num) 
{
    return eqByNumQuot(num);
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
decltype(auto) Vector<Type>::scalarProd(const Vector<Type2> &vector) const 
{
    sizesCheck(vector, __LINE__);
    return std::inner_product(cbegin(), cend(), vector.cbegin(), 
                              decltype(at(0) * vector.at(0))(0));
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
decltype(auto) Vector<Type>::operator&(const Vector<Type2> &vector) const 
{
    return scalarProd(vector);
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
decltype(auto) Vector<Type>::vectorProd(const Vector<Type2> &vector) const 
{
    vectorProdSizesCheck(vector, __LINE__);
    
    Vector<decltype(at(1) * vector.at(2) - at(2) * vector.at(1))> res(size);

    res.at(0) = at(1) * vector.at(2) - at(2) * vector.at(1);
    res.at(1) = at(2) * vector.at(0) - at(0) * vector.at(2);
    res.at(2) = at(0) * vector.at(1) - at(1) * vector.at(0);

    return res;
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
decltype(auto) Vector<Type>::operator^(const Vector<Type2> &vector) const 
{
    return vectorProd(vector);
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
Vector<Type> &Vector<Type>::eqVectorProd(const Vector<Type2> &vector) 
{
    vectorProdSizesCheck(vector, __LINE__);
    
    Type old0 = at(0);
    Type old1 = at(1);
    Type old2 = at(2);
    
    at(0) = old1 * vector.at(2) - old2 * vector.at(1);
    at(1) = old2 * vector.at(0) - old0 * vector.at(2);
    at(2) = old0 * vector.at(1) - old1 * vector.at(0);
    
    return *this;
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
Vector<Type> &Vector<Type>::operator^=(const Vector<Type2> &vector) 
{
    return eqVectorProd(vector);
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
double Vector<Type>::angle(const Vector<Type2> &vector) const
{
    double length1 = length();
    double length2 = vector.length();

    if (abs(length1) < EPS || abs(length2) < EPS)
        return 0;
    
    double dot = scalarProd(vector);
    return acos(dot / (length1 * length2));
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
bool Vector<Type>::isCollinear(const Vector<Type2> &vector) const
{
    sizesCheck(vector, __LINE__);
    double ang = angle(vector);
    return abs(ang) < EPS || abs(ang - M_PI) < EPS;
}

template<VectorElement Type>
template <SupportsSumMul<Type> Type2>
bool Vector<Type>::isOrthogonal(const Vector<Type2> &vector) const
{
    sizesCheck(vector, __LINE__);
    return abs(scalarProd(vector)) < EPS;
}

template<VectorElement Type>
bool Vector<Type>::isZero() const
{
    return abs(length()) < EPS;
}

// Allocate
template<VectorElement Type>
void Vector<Type>::allocate(typename Vector<Type>::size_type sizeValue)
{
    time_t curTime = time(NULL);
    uint line;

    try
    {
        line = __LINE__;
        data.reset(new typename Vector<Type>::value_type[sizeValue]);
    }
    catch (bad_alloc &err)
    {
        throw MemoryException(ctime(&curTime), __FILE__, line,
                              typeid(*this).name(), __FUNCTION__);
    }
}

// Checks
template<VectorElement Type>
void Vector<Type>::zeroSizeCheck(const uint line) const
{
    if (isEmpty())
    {
        time_t curTime = time(NULL);
        throw EmptyVectorException(ctime(&curTime), __FILE__,
                                   line, typeid(*this).name(),
                                   __FUNCTION__);
    }
}

template<VectorElement Type>
void Vector<Type>::indexCheck(typename Vector<Type>::size_type index, const uint line) const
{
    if (index >= getSize())
    {
        time_t curTime = time(NULL);
        throw OutOfRangesException(ctime(&curTime), __FILE__,
                                   line, typeid(*this).name(),
                                   __FUNCTION__);
    }
}

template<VectorElement Type>
template <typename Type2>
void Vector<Type>::sizesCheck(const Vector<Type2> &vector,
                              const uint line) const
{
    if (getSize() != vector.getSize())
    {
        time_t curTime = time(NULL);
        throw NotEqualSizesException(ctime(&curTime), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template<VectorElement Type>
template <typename Type2>
void Vector<Type>::vectorProdSizesCheck(const Vector<Type2> &vector,
                              const uint line) const
{
    if (getSize() != 3 || vector.getSize() != 3)
    {
        time_t curTime = time(NULL);
        throw Not3DException(ctime(&curTime), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template<VectorElement Type>
template <typename Type2>
void Vector<Type>::divisionByZeroCheck(const Type2 &num,
                              const uint line) const
{
    if (abs(num) < EPS)
    {
        time_t curTime = time(NULL);
        throw DivisionByZeroException(ctime(&curTime), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

#endif
