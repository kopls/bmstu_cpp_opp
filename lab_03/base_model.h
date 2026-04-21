#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include "visible_object.h"

class BaseModel : public VisibleObject
{
public:
    bool isComposite() const override { return false; }
};

#endif
