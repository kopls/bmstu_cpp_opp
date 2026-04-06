#ifndef ITERATOR_H
#define ITERATOR_H

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
    Iterator(const shared_ptr<value_type[]> &data, size_t limit, size_t i) noexcept;
    Iterator(const Iterator<value_type> &iterator) noexcept;

    ~Iterator() = default;

    Iterator<value_type> &operator=(const Iterator<value_type> &iterator) noexcept;

    operator bool() const noexcept;

    reference operator*();
    reference operator*() const;

    pointer operator->();
    pointer operator->() const;

    reference operator[](difference_type dif);
    reference operator[](difference_type dif) const;

    Iterator<value_type> operator+(difference_type dif) const noexcept;
    Iterator<value_type> &operator+=(difference_type dif) noexcept;

    Iterator<value_type> &operator++() noexcept;
    Iterator<value_type> operator++(int) noexcept;

    Iterator<value_type> operator-(difference_type dif) const noexcept;
    Iterator<value_type> &operator-=(difference_type dif) noexcept;

    Iterator<value_type> &operator--() noexcept;
    Iterator<value_type> operator--(int) noexcept;

    auto operator-(const Iterator<value_type>& other) const noexcept;

    bool operator==(const Iterator<value_type>& other) const noexcept;
    auto operator<=>(const Iterator<value_type> &iterator) const noexcept;

protected:
    pointer getCurPtr() const noexcept;
    void expiredCheck(const uint line) const;
    void indexCheck(const uint line) const;

private:
    std::weak_ptr<value_type[]> ptr;
};

#include "iterator.hpp"

static_assert(std::random_access_iterator<Iterator<int>>);

#endif
