#ifndef INVISIBLE_OBJECT_H
#define INVISIBLE_OBJECT_H

#include "object.h"

class InvisibleObject : public Object
{
public:
    ~InvisibleObject() override = default;

    bool isVisible() const override { return false; };
};

#endif
