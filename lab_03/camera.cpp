#include <cmath>

#include "drawer_visitor.h"
#include "camera.h"

void Camera::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}

const Point &Camera::getLocation() const
{
    return _location;
}

const Point &Camera::getRight() const
{
    return _right;
}

const Point &Camera::getUp() const
{
    return _up;
}

const Point &Camera::getForward() const
{
    return _forward;
}

double Camera::getFocalLength() const
{
    return _focalLength;
}


void rotateVector(Point &vec, const Point &angles)
{
    // Поворот вокруг X
    double radX = angles.getX() * M_PI / 180.0;
    double cosX = cos(radX);
    double sinX = sin(radX);
    double y = vec.getY() * cosX - vec.getZ() * sinX;
    double z = vec.getY() * sinX + vec.getZ() * cosX;
    vec.setY(y);
    vec.setZ(z);

    // Поворот вокруг Y
    double radY = angles.getY() * M_PI / 180.0;
    double cosY = cos(radY);
    double sinY = sin(radY);
    double x = vec.getX() * cosY + vec.getZ() * sinY;
    double z2 = vec.getZ() * cosY - vec.getX() * sinY;
    vec.setX(x);
    vec.setZ(z2);

    // Поворот вокруг Z
    double radZ = angles.getZ() * M_PI / 180.0;
    double cosZ = cos(radZ);
    double sinZ = sin(radZ);
    double x2 = vec.getX() * cosZ - vec.getY() * sinZ;
    double y2 = vec.getX() * sinZ + vec.getY() * cosZ;
    vec.setX(x2);
    vec.setY(y2);
}

void Camera::transform(const Point &move, const Point &scale, const Point &rotate)
{
    _location.move(move.getX(), move.getY(), move.getZ());

    rotateVector(_right, rotate);
    rotateVector(_up, rotate);
    rotateVector(_forward, rotate);

    _focalLength *= scale.getX();
}
