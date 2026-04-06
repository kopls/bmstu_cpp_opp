#ifndef CONST_BACKWARD_ITERATOR_HPP
#define CONST_BACKWARD_ITERATOR_HPP

#include <time.h>
#include "backward_const_iterator.h"
#include "exceptions.h"

template<VectorElement Type>
ConstBackwardIterator<Type>::ConstBackwardIterator(const shared_ptr<Type[]> &data, size_t limit, int i) noexcept 
{
    ptr = data;
    size = limit;
    index = i;
}

template<VectorElement Type>
ConstBackwardIterator<Type>::ConstBackwardIterator(const ConstBackwardIterator<Type> &iterator) noexcept 
{
    ptr = iterator.ptr;
    size = iterator.size;
    index = iterator.index;
}

template<VectorElement Type>
ConstBackwardIterator<Type> &ConstBackwardIterator<Type>::operator=(const ConstBackwardIterator<Type> &iterator) noexcept 
{
    ptr = iterator.ptr;
    size = iterator.size;
    index = iterator.index;
    return *this;
}

template<VectorElement Type>
ConstBackwardIterator<Type>::operator bool() const noexcept
{
    return size && index >= 0 && static_cast<size_t>(index) < size;
}

template<VectorElement Type>
typename ConstBackwardIterator<Type>::reference ConstBackwardIterator<Type>::operator*() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return *getCurPtr();
}

template<VectorElement Type>
typename ConstBackwardIterator<Type>::pointer ConstBackwardIterator<Type>::operator->() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return getCurPtr();
}

template<VectorElement Type>
bool ConstBackwardIterator<Type>::operator==(const ConstBackwardIterator<Type>& other) const noexcept
{
    return index == other.index;
}

template<VectorElement Type>
bool ConstBackwardIterator<Type>::operator!=(const ConstBackwardIterator<Type>& other) const noexcept
{
    return !(*this == other);
}

template<VectorElement Type>
ConstBackwardIterator<Type> &ConstBackwardIterator<Type>::operator++() noexcept
{
    --index;
    return *this;
}

template<VectorElement Type>
ConstBackwardIterator<Type> ConstBackwardIterator<Type>::operator++(int) noexcept
{
    ConstBackwardIterator<Type> tmp(*this);
    --index;
    return tmp;
}

template<VectorElement Type>
ConstBackwardIterator<Type> &ConstBackwardIterator<Type>::operator--() noexcept
{
    ++index;
    return *this;
}

template<VectorElement Type>
ConstBackwardIterator<Type> ConstBackwardIterator<Type>::operator--(int) noexcept
{
    ConstBackwardIterator<Type> tmp(*this);
    ++index;
    return tmp;
}

template<VectorElement Type>
typename ConstBackwardIterator<Type>::pointer ConstBackwardIterator<Type>::getCurPtr() const noexcept
{
    shared_ptr<Type[]> tmp = ptr.lock();
    return tmp.get() + index;
}

template<VectorElement Type>
void ConstBackwardIterator<Type>::expiredCheck(const uint line) const
{
    if (ptr.expired())
    {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

template<VectorElement Type>
void ConstBackwardIterator<Type>::indexCheck(const uint line) const
{
    if (index < 0 || static_cast<size_t>(index) >= size)
    {
        time_t curTime = time(NULL);
        throw OutOfRangesException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

#endif
