#ifndef OBJECT_H
#define OBJECT_H

class BaseVisitor;

class Object
{
public:
    virtual ~Object() = default;

    virtual void accept(BaseVisitor &visitor) = 0;

    virtual void transform(double dx, double dy) = 0;

    virtual bool isVisible() const = 0;

    virtual bool isComposite() const = 0;

    // Бегин енд
};

#endif
