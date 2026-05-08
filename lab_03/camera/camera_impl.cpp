#include "camera_impl.h"

#include <cmath>

namespace
{
constexpr double PI = 3.14159265358979323846;

void rotateVector(Point &vec, const Point &angles)
{
    double radX = angles.getX() * PI / 180.0;
    double cosX = std::cos(radX);
    double sinX = std::sin(radX);
    double y = vec.getY() * cosX - vec.getZ() * sinX;
    double z = vec.getY() * sinX + vec.getZ() * cosX;
    vec.setY(y);
    vec.setZ(z);

    double radY = angles.getY() * PI / 180.0;
    double cosY = std::cos(radY);
    double sinY = std::sin(radY);
    double x = vec.getX() * cosY + vec.getZ() * sinY;
    double z2 = vec.getZ() * cosY - vec.getX() * sinY;
    vec.setX(x);
    vec.setZ(z2);

    double radZ = angles.getZ() * PI / 180.0;
    double cosZ = std::cos(radZ);
    double sinZ = std::sin(radZ);
    double x2 = vec.getX() * cosZ - vec.getY() * sinZ;
    double y2 = vec.getX() * sinZ + vec.getY() * cosZ;
    vec.setX(x2);
    vec.setY(y2);
}
}

void CameraImpl::transform(const Point &move, const Point &scale, const Point &rotate)
{
    _location.move(move.getX(), move.getY(), move.getZ());

    rotateVector(_right, rotate);
    rotateVector(_up, rotate);
    rotateVector(_forward, rotate);

    _focalLength *= scale.getX();
}

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
