#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <memory>
#include <iterator>
#include <cstddef>
#include <compare>

#include "base_iterator.h"
#include "concept.h"

using namespace std;

template <VectorElement Type>
class Vector;

template <VectorElement Type>
class ConstIterator : BaseIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = Type;                                     
    using difference_type = ptrdiff_t;                     
    using pointer = const Type*;                                     
    using reference = const Type&;

    ConstIterator() = default;
    ConstIterator(const shared_ptr<Type[]> &data, size_t limit, size_t i) noexcept;
    ConstIterator(const ConstIterator<Type> &iterator) noexcept;

    ~ConstIterator() = default;

    ConstIterator<Type> &operator=(const ConstIterator<Type> &iterator) noexcept;

    operator bool() const;

    reference operator*() const;
    pointer operator->() const;

    reference operator[](difference_type dif) const;

    ConstIterator<Type> operator+(difference_type dif) const;
    ConstIterator<Type> &operator+=(difference_type dif);

    ConstIterator<Type> &operator++();
    ConstIterator<Type> operator++(int);

    ConstIterator<Type> operator-(difference_type dif) const;
    ConstIterator<Type> &operator-=(difference_type dif);

    ConstIterator<Type> &operator--();
    ConstIterator<Type> operator--(int);

    difference_type operator-(const ConstIterator<Type>& other) const;

    auto operator<=>(const ConstIterator<Type> &iterator) const;

protected:
    pointer getCurPtr() const;
    void expiredCheck(const uint line) const;
    void indexCheck(const uint line) const;

private:
    std::weak_ptr<Type[]> ptr;
};

#include "const_iterator.hpp"

static_assert(std::random_access_iterator<ConstIterator<int>>);

#endif
