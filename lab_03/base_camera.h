#ifndef BASE_CAMERA_H
#define BASE_CAMERA_H

#include "invisible_object.h"

class BaseCamera : public InvisibleObject
{
public:
    bool isComposite() const override { return false; }
};

#endif
