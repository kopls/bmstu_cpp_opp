#ifndef CONST_BACKWARD_ITERATOR_H
#define CONST_BACKWARD_ITERATOR_H

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
class ConstBackwardIterator : BaseIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Type;
    using difference_type = ptrdiff_t;
    using pointer = const Type*;
    using reference = const Type&;

    ConstBackwardIterator() = default;
    ConstBackwardIterator(const shared_ptr<Type[]> &data, size_t limit, int i) noexcept;
    ConstBackwardIterator(const ConstBackwardIterator<Type> &iterator) noexcept;

    ~ConstBackwardIterator() = default;

    ConstBackwardIterator<Type> &operator=(const ConstBackwardIterator<Type> &iterator) noexcept;

    operator bool() const noexcept;

    reference operator*() const;
    pointer operator->() const;

    ConstBackwardIterator<Type> &operator++() noexcept;
    ConstBackwardIterator<Type> operator++(int) noexcept;

    ConstBackwardIterator<Type> &operator--() noexcept;
    ConstBackwardIterator<Type> operator--(int) noexcept;

    bool operator==(const ConstBackwardIterator<Type>& other) const noexcept;
    bool operator!=(const ConstBackwardIterator<Type>& other) const noexcept;

protected:
    pointer getCurPtr() const noexcept;
    void expiredCheck(const uint line) const;
    void indexCheck(const uint line) const;

private:
    weak_ptr<Type[]> ptr;
};

#include "backward_const_iterator.hpp"

static_assert(std::bidirectional_iterator<ConstBackwardIterator<int>>);

#endif
