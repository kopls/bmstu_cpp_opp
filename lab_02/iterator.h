#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>
#include <iterator>
#include <cstddef>
#include <compare>

#include "base_iterator.h"

using namespace std;

template <typename Type>
class Vector;

template <typename Type>
class Iterator : BaseIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = Type;                                     
    using difference_type = ptrdiff_t;                     
    using pointer = Type*;                                     
    using reference = Type&;
    using rvalue_reference = Type&&;
    using const_rvalue_reference = const Type&&;

    Iterator() = default;
    Iterator(const shared_ptr<Type[]> &data, size_t limit, size_t i) noexcept;
    Iterator(const Iterator<Type> &iterator) noexcept;

    ~Iterator() = default;

    Iterator<Type> &operator=(const Iterator<Type> &iterator) noexcept;

    operator bool() const;

    Type &operator*();
    Type &operator*() const;

    Type *operator->();
    Type *operator->() const;

    Type& operator[](difference_type dif);
    Type& operator[](difference_type dif) const;

    Iterator<Type> operator+(difference_type dif) const;
    Iterator<Type> &operator+=(difference_type dif);

    Iterator<Type> &operator++();
    Iterator<Type> operator++(int);

    Iterator<Type> operator-(difference_type dif) const;
    Iterator<Type> &operator-=(difference_type dif);

    Iterator<Type> &operator--();
    Iterator<Type> operator--(int);

    auto operator-(const Iterator<Type>& other) const;

    auto operator<=>(const Iterator<Type> &iterator) const;

protected:
    Type *getCurPtr() const;
    void expiredCheck(const uint line) const;
    void indexCheck(const uint line) const;

private:
    std::weak_ptr<Type[]> ptr;
};

#include "iterator.hpp"

static_assert(std::random_access_iterator<Iterator<int>>);

#endif
