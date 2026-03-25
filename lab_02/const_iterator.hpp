#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <time.h>
#include "iterator.h"
#include "exceptions.h"

template <typename Type>
ConstIterator<Type>::ConstIterator(const shared_ptr<Type[]> &data, size_t limit, size_t i) noexcept 
{
    ptr = data;
    size = limit;
    index = i;
}

template <typename Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &iterator) noexcept 
{
    ptr = iterator.ptr;
    size = iterator.size;
    index = iterator.index;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(const ConstIterator<Type> &iterator) noexcept 
{
    ptr.reset(iterator.ptr);
    size = iterator.size;
    index = iterator.index;
}

template <typename Type>
ConstIterator<Type>::operator bool() const 
{
    expiredCheck(__LINE__);

    return size && index < size;
}

template <typename Type>
const Type &ConstIterator<Type>::operator*() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return *getCurPtr();
}

template <typename Type>
const Type *ConstIterator<Type>::operator->() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return getCurPtr();
}

template <typename Type>
const Type &ConstIterator<Type>::operator[](difference_type dif) const 
{ 
    return *(*this + dif);
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator+(difference_type dif) const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    ConstIterator<Type> it(*this);
    it.index += dif;

    return it;
}

template<typename Type>
ConstIterator<Type> operator+(typename ConstIterator<Type>::difference_type n, const ConstIterator<Type>& it)
{
    return it + n;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator+=(difference_type dif) 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    index += dif;
    return *this;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator++() 
{
    expiredCheck(__LINE__);

    ++index; 
    return *this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int) 
{
    expiredCheck(__LINE__);
    
    ConstIterator<Type> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator-(difference_type dif) const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    ConstIterator<Type> it(*this);
    it.index -= dif;

    return it;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(difference_type dif) 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    index -= dif;
    return *this;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator--() 
{
    expiredCheck(__LINE__);
    
    --index;

    return *this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int) 
{
    expiredCheck(__LINE__);

    ConstIterator<Type> tmp(*this);
    --(*this);

    return tmp;
}

template <typename Type>
auto ConstIterator<Type>::operator-(const ConstIterator<Type>& other) const 
{
    return static_cast<difference_type>(index) - static_cast<difference_type>(other.index);
}

template <typename Type>
auto ConstIterator<Type>::operator<=>(const ConstIterator<Type> &iterator) const
{
    iterator.expiredCheck(__LINE__);
    expiredCheck(__LINE__);

    return getCurPtr() <=> iterator.getCurPtr();
}

template <typename Type>
const Type *ConstIterator<Type>::getCurPtr() const
{
    shared_ptr<Type[]> tmp = ptr.lock();
    return tmp.get() + index;
}

template <typename Type>
void ConstIterator<Type>::expiredCheck(const uint line) const
{
    if (ptr.expired())
    {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

template <typename Type>
void ConstIterator<Type>::indexCheck(const uint line) const
{
    if (index >= size)
    {
        time_t curTime = time(NULL);
        throw OutOfRangesException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

#endif
