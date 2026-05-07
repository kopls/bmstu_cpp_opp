#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    virtual void build() = 0;
    virtual bool isBuild() const = 0;
};

#endif
