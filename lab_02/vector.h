#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

#include "base_container.h"

#include "iterator.h"
#include "const_iterator.h"
#include "backward_iterator.h"
#include "backward_const_iterator.h"

#include "concept.h"

using namespace std;

template <VectorElement Type>
class Vector : public BaseContainer
{
public:
    // ========== TYPE ALIASES ==========
    using value_type = Type;
    using reference = Type&;
    using const_reference = const Type&;
    using pointer = Type*;
    using const_pointer = const Type*;
    using size_type = size_t;
    using iterator = Iterator<Type>;
    using const_iterator = ConstIterator<Type>;
    using reverse_iterator = BackwardIterator<Type>;
    using const_reverse_iterator = ConstBackwardIterator<Type>;

    // ========== CONSTRUCTORS ==========
    Vector() = default;
    explicit Vector(size_type sizeValue);

    explicit Vector(const Vector &vector);

    template <ConvertibleTo<Type> Type2>
    explicit Vector(const Vector<Type2> &vector);

    Vector(size_type sizeValue, const_reference filler);

    template <ConvertibleTo<Type> Type2>
    Vector(size_type sizeValue, const Type2 &filler);

    Vector(size_type sizeValue, const_pointer arr);

    template <ConvertibleTo<Type> Type2>
    Vector(size_type sizeValue, const Type2 *arr);

    Vector(initializer_list<value_type> elements);
    
    template<ConvertibleTo<Type> Type2>
    Vector(initializer_list<Type2> elements);

    Vector(Vector &&vector) noexcept;

    template<input_iterator Iter, sentinel_for<Iter> Sent>
    requires ConvertibleTo<iter_value_t<Iter>, value_type>
    Vector(const Iter& begin, const Sent& end);

    template<std::ranges::input_range Range>
    requires ConvertibleTo<std::ranges::range_value_t<Range>, value_type>
    Vector(Range&& range);

    ~Vector() override = default;

    // ========== ASSIGNMENT OPERATORS ==========
    Vector &operator=(const Vector &vector);
    Vector &operator=(Vector &&vector) noexcept;

    template<ConvertibleTo<Type> Type2>
    Vector &operator=(const Vector<Type2> &vector);

    template<ConvertibleTo<Type> Type2>
    Vector &operator=(initializer_list<Type2> elements);

    // ========== COMPARISON OPERATORS ==========
    template<EqualityComparableWith<Type> Type2>
    bool operator==(const Vector<Type2> &vector) const;

    template<EqualityComparableWith<Type> Type2>
    bool isEqual(const Vector<Type2> &vector) const;

    template<EqualityComparableWith<Type> Type2>
    bool operator!=(const Vector<Type2> &vector) const;

    template<EqualityComparableWith<Type> Type2>
    bool isNotEqual(const Vector<Type2> &vector) const;

    // ========== VECTOR METRICS ==========
    template<ConvertibleTo<double> U = Type>
    Type length() const;

    template<ConvertibleTo<double> U = Type>
    Vector<Type> getUnit() const;

    // ========== ELEMENT ACCESS ==========
    reference at(size_type index);
    reference operator[](size_type index);

    const_reference at(size_type index) const;
    const_reference operator[](size_type index) const;

    // ========== VECTOR-VECTOR ARITHMETIC ==========
    template <SupportSum<Type> Type2>
    decltype(auto) vecSum(const Vector<Type2> &vector) const;

    template <SupportSum<Type> Type2>
    decltype(auto) operator+(const Vector<Type2> &vector) const;

    template <SupportSub<Type> Type2>
    decltype(auto) vecDiff(const Vector<Type2> &vector) const;

    template <SupportSub<Type> Type2>
    decltype(auto) operator-(const Vector<Type2> &vector) const;

    template <SupportProd<Type> Type2>
    decltype(auto) vecProd(const Vector<Type2> &vector) const;

    template <SupportProd<Type> Type2>
    decltype(auto) operator*(const Vector<Type2> &vector) const;

    template <SupportQuot<Type> Type2>
    decltype(auto) vecQuot(const Vector<Type2> &vector) const;

    template <SupportQuot<Type> Type2>
    decltype(auto) operator/(const Vector<Type2> &vector) const;

    // ========== VECTOR-SCALAR ARITHMETIC ==========
    template <SupportSum<Type> Type2>
    decltype(auto) byNumSum(const Type2 &num) const;

    template <SupportSum<Type> Type2>
    decltype(auto) operator+(const Type2 &num) const;

    template <SupportSub<Type> Type2>
    decltype(auto) byNumDiff(const Type2 &num) const;

    template <SupportSub<Type> Type2>
    decltype(auto) operator-(const Type2 &num) const;

    template <SupportProd<Type> Type2>
    decltype(auto) byNumProd(const Type2 &num) const;

    template <SupportProd<Type> Type2>
    decltype(auto) operator*(const Type2 &num) const;

    template <SupportQuot<Type> Type2>
    decltype(auto) byNumQuot(const Type2 &num) const;

    template <SupportQuot<Type> Type2>
    decltype(auto) operator/(const Type2 &num) const;

    // ========== IN-PLACE VECTOR-VECTOR OPERATIONS ==========
    template <SupportSum<Type> Type2>
    Vector &eqVecSum(const Vector<Type2> &vector);

    template <SupportSum<Type> Type2>
    Vector &operator+=(const Vector<Type2> &vector);

    template <SupportSub<Type> Type2>
    Vector &eqVecDiff(const Vector<Type2> &vector);

    template <SupportSub<Type> Type2>
    Vector &operator-=(const Vector<Type2> &vector);

    template <SupportProd<Type> Type2>
    Vector &eqVecProd(const Vector<Type2> &vector);

    template <SupportProd<Type> Type2>
    Vector &operator*=(const Vector<Type2> &vector);

    template <SupportQuot<Type> Type2>
    Vector &eqVecQuot(const Vector<Type2> &vector);

    template <SupportQuot<Type> Type2>
    Vector &operator/=(const Vector<Type2> &vector);

    // ========== IN-PLACE VECTOR-SCALAR OPERATIONS ==========
    template <SupportSum<Type> Type2>
    Vector &eqByNumSum(const Type2 &num);

    template <SupportSum<Type> Type2>
    Vector &operator+=(const Type2 &num);

    template <SupportSub<Type> Type2>
    Vector &eqByNumDiff(const Type2 &num);

    template <SupportSub<Type> Type2>
    Vector &operator-=(const Type2 &num);

    template <SupportProd<Type> Type2>
    Vector &eqByNumProd(const Type2 &num);

    template <SupportProd<Type> Type2>
    Vector &operator*=(const Type2 &num);

    template <SupportQuot<Type> Type2>
    Vector &eqByNumQuot(const Type2 &num);

    template <SupportQuot<Type> Type2>
    Vector &operator/=(const Type2 &num);
    
    // ========== UNARY OPERATIONS ==========
    template<ConvertibleTo<double> U = Type>
    Vector<Type> neg() const;

    template<ConvertibleTo<double> U = Type>
    Vector<Type> operator-() const;

    // ========== SCAL & VEC PRODUCTS ==========
    template <SupportsSumMul<Type> Type2>
    decltype(auto) scalarProd(const Vector<Type2> &vector) const;

    template <SupportsSumMul<Type> Type2>
    decltype(auto) operator&(const Vector<Type2> &vector) const;

    template <SupportsSumMul<Type> Type2>
    decltype(auto) vectorProd(const Vector<Type2> &vector) const;

    template <SupportsSumMul<Type> Type2>
    decltype(auto) operator^(const Vector<Type2> &vector) const;

    template <SupportsSumMul<Type> Type2>
    Vector &eqVectorProd(const Vector<Type2> &vector);

    template <SupportsSumMul<Type> Type2>
    Vector &operator^=(const Vector<Type2> &vector);

    // ========== GEOMETRIC UTILITIES ==========
    template <SupportsSumMul<Type> Type2>
    double angle(const Vector<Type2> &vector) const;

    template <SupportsSumMul<Type> Type2>
    bool isCollinear(const Vector<Type2> &vector) const;

    template <SupportsSumMul<Type> Type2>
    bool isOrthogonal(const Vector<Type2> &vector) const;

    bool isZero() const;

    // ========== ITERATORS ==========
    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

protected:
    void allocate(size_type sizeValue);
    void zeroSizeCheck(const uint line) const;
    void indexCheck(const size_type index, const uint line) const;

    template <typename Type2>
    void sizesCheck(const Vector<Type2> &vector, const uint line) const;

    template <typename Type2>
    void vectorProdSizesCheck(const Vector<Type2> &vector, const uint line) const;

    template <typename Type2>
    void divisionByZeroCheck(const Type2 &num, const uint line) const;

private:
    shared_ptr<value_type[]> data = nullptr;
};

#include "vector.hpp"

#endif
