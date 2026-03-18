#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <time.h>
#include "iterator.h"
#include "exceptions.h"

template <typename Type>
Iterator<Type>::Iterator(const Vector<Type> &vector) noexcept 
{
    ptr = vector.data;
    size = vector.size;
    index = 0;
}

template <typename Type>
Iterator<Type>::Iterator(const Iterator<Type> &iterator) noexcept 
{
    ptr = itreator.ptr;
    size = iterator.size;
    index = iterator.index;
}

template <typename Type>
Iterator<Type> &Iterator<Type>::operator=(const Iterator<Type> &iterator) noexcept 
{
    ptr.reset(iterator.ptr);
    size = iterator.size;
    index = iterator.index;
}

template <typename Type>
Iterator<Type>::operator bool() const 
{
    expiredCheck(__LINE__);

    return size && index < size;
}

template <typename Type>
Type &Iterator<Type>::operator*() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return *getCurPtr();
}

template <typename Type>
const Type &Iterator<Type>::operator*() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return *getCurPtr();
}

template <typename Type>
Type *Iterator<Type>::operator->() 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return getCurPtr();
}

template <typename Type>
const Type *Iterator<Type>::operator->() const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    return getCurPtr();
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator+(size_t dif) const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    Iterator<Type> it(*this);
    it.index += dif;

    return it;
}

template <typename Type>
Iterator<Type> &Iterator<Type>::operator+=(size_t dif) 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    index += dif;
    return *this;
}

template <typename Type>
Iterator<Type> &Iterator<Type>::operator++() 
{
    expiredCheck(__LINE__);

    ++index; 
    return *this;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator++(int) 
{
    expiredCheck(__LINE__);
    
    Iterator<Type> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator-(size_t dif) const 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    Iterator<Type> it(*this);
    it.index -= dif;

    return it;
}

template <typename Type>
Iterator<Type> &Iterator<Type>::operator-=(size_t dif) 
{
    expiredCheck(__LINE__);
    indexCheck(__LINE__);

    index -= dif;
    return *this;
}

template <typename Type>
Iterator<Type> &Iterator<Type>::operator--() 
{
    expiredCheck(__LINE__);
    
    --index;

    return *this
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator--(int) 
{
    expiredCheck(__LINE__);

    Iterator<Type> tmp(*this);
    --(*this);

    return tmp;
}

template <typename Type>
auto operator<=>(const Iterator<Type> &iterator) const
{
    iterator.expiredCheck(__LINE__);
    expiredCheck(__LINE__);

    return getCurPtr() <=> iterator.getCurPtr();
}

template <typename Type>
Type *Iterator<Type>::getCurPtr() const
{
    shared_ptr<Type[]> tmp = ptr.lock();
    return tmp.get + index;
}

template <typename Type>
void Iterator<Type>::expiredCheck(const uint line) const
{
    if (ptr.expired())
    {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

template <typename Type>
void Iterator<Type>::indexCheck(const uint line) const
{
    if (index >= size)
    {
        time_t curTime = time(NULL);
        throw OutOfRangeException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

#endif
