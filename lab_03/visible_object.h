#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include "object.h"

class VisibleObject : public Object
{
public:
    bool isVisible() const override { return true; }
}

#endif
