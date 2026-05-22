#ifndef BASE_CAMERA_IMPL_H
#define BASE_CAMERA_IMPL_H

#include "point.h"

class BaseCameraImpl
{
public:
    virtual ~BaseCameraImpl() = default;

    virtual Point project(const Point &point) const = 0;

    virtual Point &getLocation() = 0;
    virtual const Point &getLocation() const = 0;

    virtual Point &getRight() = 0;
    virtual const Point &getRight() const = 0;

    virtual Point &getUp() = 0;
    virtual const Point &getUp() const = 0;

    virtual Point &getForward() = 0;
    virtual const Point &getForward() const = 0;

    virtual double &getFocalLength() = 0;
};

#endif
