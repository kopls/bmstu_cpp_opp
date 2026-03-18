#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <time.h>
#include "iterator.h"
#include "exceptions.h"

template <typename Type>
ConstIterator<Type>::ConstIterator(const Vector<Type> &vector) noexcept 
{
    ptr = vector.data;
    size = vector.size;
    index = 0;
}

template <typename Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &iterator) noexcept 
{
    ptr = itreator.ptr;
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
Type &ConstIterator<Type>::operator*() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return *getCurPtr();
}

template <typename Type>
const Type &ConstIterator<Type>::operator*() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return *getCurPtr();
}

template <typename Type>
Type *ConstIterator<Type>::operator->() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return getCurPtr();
}

template <typename Type>
const Type *ConstIterator<Type>::operator->() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return getCurPtr();
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator+(size_t dif) const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    ConstIterator<Type> it(*this);
    it.index += dif;

    return it;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator+=(size_t dif) 
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
ConstIterator<Type> ConstIterator<Type>::operator-(size_t dif) const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    ConstIterator<Type> it(*this);
    it.index -= dif;

    return it;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(size_t dif) 
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

    return *this
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
auto operator<=>(const ConstIterator<Type> &iterator) const
{
    iterator.expiredCheck(__LINE__);
    expiredCheck(__LINE__);

    return getCurPtr() <=> iterator.getCurPtr();
}

template <typename Type>
const Type *ConstIterator<Type>::getCurPtr() const
{
    shared_ptr<Type[]> tmp = ptr.lock();
    return tmp.get + index;
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
        throw OutOfRangeException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

#endif
