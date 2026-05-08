#ifndef CAMERA_IMPL_H
#define CAMERA_IMPL_H

#include "point.h"

class CameraImpl : public BaseCameraImpl
{
public:
    ~BaseCameraImpl() override = default;
    CameraImpl(const Point &location) 
        : _location(location)
        , _right(1, 0, 0)
        , _up(0, 1, 0)
        , _forward(0, 0, 1)
        , _focalLength(1.0)
    {}

    void transform(const Point &move, const Point &scale, const Point &rotate) override;
    Point project(const Point &point) const override;
    const Point &getLocation() const override;

private:
    Point _location;
    Point _right;
    Point _up;
    Point _forward;
    double _focalLength;
};

#endif
