#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <memory>
#include <iterator>

template <typename Type>
class Vector;

template <typename Type>
class ConstIterator : public iterator<random_access_iterator_tag, Type>
{
    friend class Vector<Type>;

public:
    ConstIterator(const Vector<Type> &vector) noexcept;
    ConstIterator(const ConstIterator<Type> &iterator) noexcept;

    ~ConstIterator() = default;

    ConstIterator<Type> &operator=(const ConstIterator<Type> &iterator) noexcept;

    operator bool() const;

    const Type & operator*() const;
    const Type * operator->() const;

    ConstIterator<Type> operator+(size_t dif) const;
    ConstIterator<Type> &operator+=(size_t dif);

    ConstIterator<Type> &operator++();
    ConstIterator<Type> operator++(int);

    ConstIterator<Type> operator-(size_t dif) const;
    ConstIterator<Type> &operator-=(size_t dif);

    ConstIterator<Type> &operator--();
    ConstIterator<Type> operator--(int);

    auto operator<=>(const ConstIterator<Type> &iterator) const = default;

protected:
    const Type *getCurPtr() const;
    void exprideCheck(const uint line) const;
    void indexCheck(const uint line) const;

private:
    std::weak_ptr<Type[]> ptr;
    size_t size = 0;
    size_t index = 0;
};

#endif
