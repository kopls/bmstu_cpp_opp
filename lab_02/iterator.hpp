#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <time.h>
#include "iterator.h"
#include "exceptions.h"

template<VectorElement Type>
Iterator<Type>::Iterator(const shared_ptr<typename Iterator<Type>::value_type[]> &data, size_t limit, size_t i) noexcept 
{
    ptr = data;
    size = limit;
    index = i;
}

template<VectorElement Type>
Iterator<Type>::Iterator(const Iterator<typename Iterator<Type>::value_type> &iterator) noexcept 
{
    ptr = iterator.ptr;
    size = iterator.size;
    index = iterator.index;
}

template<VectorElement Type>
Iterator<Type> &Iterator<Type>::operator=(const Iterator<typename Iterator<Type>::value_type> &iterator) noexcept 
{
    ptr = iterator.ptr;
    size = iterator.size;
    index = iterator.index;
    return *this;
}

template<VectorElement Type>
Iterator<Type>::operator bool() const noexcept
{
    return size && index < size;
}

template<VectorElement Type>
typename Iterator<Type>::reference Iterator<Type>::operator*() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return *getCurPtr();
}

template<VectorElement Type>
typename Iterator<Type>::reference Iterator<Type>::operator*() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return *getCurPtr();
}

template<VectorElement Type>
typename Iterator<Type>::pointer Iterator<Type>::operator->() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return getCurPtr();
}

template<VectorElement Type>
typename Iterator<Type>::pointer Iterator<Type>::operator->() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);
    return getCurPtr();
}

template<VectorElement Type>
typename Iterator<Type>::reference Iterator<Type>::operator[](difference_type dif) 
{
    return *(*this + dif);
}

template<VectorElement Type>
typename Iterator<Type>::reference Iterator<Type>::operator[](difference_type dif) const 
{ 
    return *(*this + dif);
}

template<VectorElement Type>
Iterator<Type> Iterator<Type>::operator+(difference_type dif) const noexcept
{
    Iterator<Type> it(*this);
    it.index += dif;
    return it;
}

template<VectorElement Type>
Iterator<Type> operator+(typename Iterator<Type>::difference_type n, const Iterator<Type>& it) noexcept
{
    return it + n;
}

template<VectorElement Type>
Iterator<Type> &Iterator<Type>::operator+=(difference_type dif) noexcept
{
    index += dif;
    return *this;
}

template<VectorElement Type>
Iterator<Type> &Iterator<Type>::operator++() noexcept
{
    ++index; 
    return *this;
}

template<VectorElement Type>
Iterator<Type> Iterator<Type>::operator++(int) noexcept
{
    Iterator<Type> tmp(*this);
    ++(*this);
    return tmp;
}

template<VectorElement Type>
Iterator<Type> Iterator<Type>::operator-(difference_type dif) const noexcept
{
    Iterator<Type> it(*this);
    it.index -= dif;
    return it;
}

template<VectorElement Type>
Iterator<Type> &Iterator<Type>::operator-=(difference_type dif) noexcept
{
    index -= dif;
    return *this;
}

template<VectorElement Type>
Iterator<Type> &Iterator<Type>::operator--() noexcept
{
    --index;
    return *this;
}

template<VectorElement Type>
Iterator<Type> Iterator<Type>::operator--(int) noexcept
{
    Iterator<Type> tmp(*this);
    --(*this);
    return tmp;
}

template<VectorElement Type>
auto Iterator<Type>::operator-(const Iterator<Type>& other) const noexcept
{
    return static_cast<difference_type>(index) - static_cast<difference_type>(other.index);
}

template<VectorElement Type>
bool Iterator<Type>::operator==(const Iterator<value_type>& other) const noexcept
{
    return index == other.index && size == other.size;
}

template<VectorElement Type>
auto Iterator<Type>::operator<=>(const Iterator<Type> &iterator) const noexcept
{
    return getCurPtr() <=> iterator.getCurPtr();
}

template<VectorElement Type>
typename Iterator<Type>::pointer Iterator<Type>::getCurPtr() const noexcept
{
    shared_ptr<typename Iterator<Type>::value_type[]> tmp = ptr.lock();
    return tmp.get() + index;
}

template<VectorElement Type>
void Iterator<Type>::expiredCheck(const uint line) const
{
    if (ptr.expired())
    {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

template<VectorElement Type>
void Iterator<Type>::indexCheck(const uint line) const
{
    if (index >= size)
    {
        time_t curTime = time(NULL);
        throw OutOfRangesException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

#endif
