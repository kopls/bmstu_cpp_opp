#ifndef BACKWARD_ITERATOR_HPP
#define BACKWARD_ITERATOR_HPP

#include <time.h>
#include "backward_iterator.h"
#include "exceptions.h"

template<VectorElement Type>
BackwardIterator<Type>::BackwardIterator(const shared_ptr<typename BackwardIterator<Type>::value_type[]> &data, size_t limit, int i) noexcept 
{
    ptr = data;
    size = limit;
    index = i;
}

template<VectorElement Type>
BackwardIterator<Type>::BackwardIterator(const BackwardIterator<typename BackwardIterator<Type>::value_type> &iterator) noexcept 
{
    ptr = iterator.ptr;
    size = iterator.size;
    index = iterator.index;
}

template<VectorElement Type>
BackwardIterator<Type> &BackwardIterator<Type>::operator=(const BackwardIterator<typename BackwardIterator<Type>::value_type> &iterator) noexcept 
{
    ptr = iterator.ptr;
    size = iterator.size;
    index = iterator.index;
    return *this;
}

template<VectorElement Type>
BackwardIterator<Type>::operator bool() const noexcept
{
    return size && static_cast<size_t>(index) < size;
}

template<VectorElement Type>
typename BackwardIterator<Type>::reference BackwardIterator<Type>::operator*() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return *getCurPtr();
}

template<VectorElement Type>
typename BackwardIterator<Type>::reference BackwardIterator<Type>::operator*() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return *getCurPtr();
}

template<VectorElement Type>
typename BackwardIterator<Type>::pointer BackwardIterator<Type>::operator->() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return getCurPtr();
}

template<VectorElement Type>
typename BackwardIterator<Type>::pointer BackwardIterator<Type>::operator->() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return getCurPtr();
}

template<VectorElement Type>
bool BackwardIterator<Type>::operator==(const BackwardIterator<Type>& other) const noexcept
{
    return index == other.index;
}

template<VectorElement Type>
bool BackwardIterator<Type>::operator!=(const BackwardIterator<Type>& other) const noexcept
{
    return !(*this == other);
}

template<VectorElement Type>
BackwardIterator<Type> &BackwardIterator<Type>::operator++() noexcept
{
    --index;
    return *this;
}

template<VectorElement Type>
BackwardIterator<Type> BackwardIterator<Type>::operator++(int) noexcept
{
    BackwardIterator<Type> tmp(*this);
    --index;
    return tmp;
}

template<VectorElement Type>
BackwardIterator<Type> &BackwardIterator<Type>::operator--() noexcept
{
    ++index;
    return *this;
}

template<VectorElement Type>
BackwardIterator<Type> BackwardIterator<Type>::operator--(int) noexcept
{
    BackwardIterator<Type> tmp(*this);
    ++index;
    return tmp;
}

template<VectorElement Type>
typename BackwardIterator<Type>::pointer BackwardIterator<Type>::getCurPtr() const noexcept
{
    shared_ptr<typename BackwardIterator<Type>::value_type[]> tmp = ptr.lock();
    return tmp.get() + index;
}

template<VectorElement Type>
void BackwardIterator<Type>::expiredCheck(const uint line) const
{
    if (ptr.expired())
    {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

template<VectorElement Type>
void BackwardIterator<Type>::indexCheck(const uint line) const
{
    if (static_cast<size_t>(index) >= size)
    {
        time_t curTime = time(NULL);
        throw OutOfRangesException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

#endif
