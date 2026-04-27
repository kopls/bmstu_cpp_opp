#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

#include "point.h"

class BaseVisitor;

class Object;

using Iterator = std::vector<std::shared_ptr<Object>>::iterator;

class Object
{
public:
    Object() { _id = _nextId++; };
    virtual ~Object() = default;

    virtual bool add(const std::shared_ptr<Object> &) { return false; };
    virtual bool remove(const Iterator &) { return false; };

    virtual void accept(BaseVisitor &visitor) = 0;

    virtual void transform(const Point &move, const Point &scale, const Point &rotate) = 0;

    virtual bool isVisible() const { return false; };
    virtual bool isComposite() const { return false; };

    virtual Iterator begin() { return Iterator(); };
    virtual Iterator end() { return Iterator(); };

    virtual std::size_t getId() { return _id; }

protected:
    std::size_t _id;
    static std::size_t _nextId;
};

#endif
