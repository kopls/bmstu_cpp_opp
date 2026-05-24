#ifndef BASE_CAMERA_H
#define BASE_CAMERA_H

#include "invisible_object.h"
#include "point.h"

class BaseCamera : public InvisibleObject
{
public:
    ~BaseCamera() override = default;

    bool isComposite() const override { return false; }
    bool isCamera() const override { return true; }
    BaseCamera *cameraPtr() override { return this; }
    const BaseCamera *cameraPtr() const override { return this; }

    virtual Point project(const Point &point) const = 0;
    virtual const Point &getLocation() const = 0;
    virtual const Point &getRight() const = 0;
    virtual const Point &getUp() const = 0;
    virtual const Point &getForward() const = 0;
};

#endif
