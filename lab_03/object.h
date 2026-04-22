#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

class BaseVisitor;

class Object
{
public:
    virtual ~Object() = default;

    virtual bool add(std::shared_ptr<Object> &element) = 0;
    virtual bool remove(const Iterator &iter) = 0;

    virtual void accept(BaseVisitor &visitor) = 0;

    //virtual void transform(double dx, double dy) = 0;

    virtual bool isVisible() const = 0;
    virtual bool isComposite() const = 0;

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
};

#endif
