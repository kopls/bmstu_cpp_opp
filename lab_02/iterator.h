#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>

template <typename Type>
class Vector;

template <typename Type>
class Iterator : public iterator<random_access_iterator_tag, Type>
{
    friend class Vector<Type>;

public:
    Iterator(const Vector<Type> &vector) noexcept;
    Iterator(const Iterator<Type> &iterator) noexcept;

    ~Iterator() = default;

    Iterator<Type> &operator=(const Iterator<Type> &iterator) noexcept;

    operator bool() const;

    Type & operator*();
    const Type & operator*() const;

    Type * operator->();
    const Type * operator->() const;

    Iterator<Type> operator+(size_t dif) const;
    Iterator<Type> &operator+=(size_t dif);

    Iterator<Type> &operator++();
    Iterator<Type> operator++(int);

    Iterator<Type> operator-(size_t dif) const;
    Iterator<Type> &operator-=(size_t dif);

    Iterator<Type> &operator--();
    Iterator<Type> operator--(int);

    auto operator<=>(const Iterator<Type> &iterator) const = default;

protected:
    Type *getCurPtr() const;
    void exprideCheck(const uint line) const;
    void indexCheck(const uint line) const;

private:
    std::weak_ptr<Type[]> ptr;
    size_t size = 0;
    size_t index = 0;
};

#endif
