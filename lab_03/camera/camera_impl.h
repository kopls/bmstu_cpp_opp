#ifndef CAMERA_IMPL_H
#define CAMERA_IMPL_H

#include "base_camera_impl.h"
#include "point.h"

class CameraImpl : public BaseCameraImpl
{
public:
    CameraImpl() = default;
    explicit CameraImpl(const Point &location)
        : _location(location)
        , _right(1, 0, 0)
        , _up(0, 1, 0)
        , _forward(0, 0, 1)
        , _focalLength(1.0)
    {}

    ~CameraImpl() override = default;

    Point project(const Point &point) const override;
    const Point &getLocation() const override;
    const Point &getRight() const override;
    const Point &getUp() const override;
    const Point &getForward() const override;

//private:
    Point _location;
    Point _right;
    Point _up;
    Point _forward;
    double _focalLength{1.0};
};

#endif
