#include "camera_impl.h"

#include <cmath>

Point CameraImpl::project(const Point &point) const
{
    double dx = point.getX() - _location.getX();
    double dy = point.getY() - _location.getY();
    double dz = point.getZ() - _location.getZ();

    double x = dx * _right.getX() + dy * _right.getY() + dz * _right.getZ();
    double y = dx * _up.getX() + dy * _up.getY() + dz * _up.getZ();
    double z = dx * _forward.getX() + dy * _forward.getY() + dz * _forward.getZ();

    if (z <= 0)
        return Point(0, 0, 0);

    double screenX = x * _focalLength / z;
    double screenY = y * _focalLength / z;

    screenX = (screenX + 1) * 800 / 2;
    screenY = (1 - screenY) * 600 / 2;

    return Point(screenX, screenY, 0);
}

const Point &CameraImpl::getLocation() const
{
    return _location;
}

const Point &CameraImpl::getRight() const
{
    return _right;
}

const Point &CameraImpl::getUp() const
{
    return _up;
}

const Point &CameraImpl::getForward() const
{
    return _forward;
}
