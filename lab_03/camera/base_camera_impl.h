#ifndef BASE_CAMERA_IMPL_H
#define BASE_CAMERA_IMPL_H

#include "point.h"

class BaseCameraImpl
{
public:
    virtual ~BaseCameraImpl() = default;

    virtual void transform(const Point &move, const Point &scale, const Point &rotate) = 0;
    virtual Point project(const Point &point) const = 0;
    virtual const Point &getLocation() const = 0;
};

#endif
