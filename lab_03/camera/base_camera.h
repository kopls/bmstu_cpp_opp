#ifndef BASE_CAMERA_H
#define BASE_CAMERA_H

#include "invisible_object.h"

class BaseCamera : public InvisibleObject
{
public:
    bool isComposite() const override { return false; }
    virtual Point project(const Point &point) const = 0;
    virtual const Point &getLocation() const = 0;
};

#endif
