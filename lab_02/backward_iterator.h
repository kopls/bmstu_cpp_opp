#ifndef BACKWARD_ITERATOR_H
#define BACKWARD_ITERATOR_H

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
class BackwardIterator : BaseIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Type;
    using difference_type = ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;
    using const_reference = const Type&;
    using const_pointer = const Type*;

    BackwardIterator() = default;
    BackwardIterator(const shared_ptr<value_type[]> &data, size_t limit, int i) noexcept;
    BackwardIterator(const BackwardIterator<value_type> &iterator) noexcept;

    ~BackwardIterator() = default;

    BackwardIterator<value_type> &operator=(const BackwardIterator<value_type> &iterator) noexcept;

    operator bool() const noexcept;

    reference operator*();
    reference operator*() const;

    pointer operator->();
    pointer operator->() const;

    BackwardIterator<value_type> &operator++() noexcept;
    BackwardIterator<value_type> operator++(int) noexcept;

    BackwardIterator<value_type> &operator--() noexcept;
    BackwardIterator<value_type> operator--(int) noexcept;

    bool operator==(const BackwardIterator<value_type>& other) const noexcept;
    bool operator!=(const BackwardIterator<value_type>& other) const noexcept;

protected:
    pointer getCurPtr() const noexcept;
    void expiredCheck(const uint line) const;
    void indexCheck(const uint line) const;

private:
    weak_ptr<value_type[]> ptr;
};

#include "backward_iterator.hpp"

static_assert(std::bidirectional_iterator<BackwardIterator<int>>);

#endif
