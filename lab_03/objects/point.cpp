#include <cmath>

#include "point.h"

Point::Point(const double x, const double y, const double z)
{
    setX(x);
    setY(y);
    setZ(z);
}

double Point::getX() const
{
    return _x;
}

double Point::getY() const
{
    return _y;
}

double Point::getZ() const
{
    return _z;
}

void Point::setX(const double x)
{
    _x = x;
}

void Point::setY(const double y)
{
    _y = y;
}

void Point::setZ(const double z)
{
    _z = z;
}

void Point::move(const double dx, const double dy, const double dz)
{
    setX(_x + dx);
    setY(_y + dy);
    setZ(_z + dz);
}

void Point::scale(const double kx, const double ky, const double kz)
{
    setX(_x * kx);
    setY(_y * ky);
    setZ(_z * kz);
}

void Point::rotate(const double ox, const double oy, const double oz)
{
    rotateX(ox);
    rotateY(oy);
    rotateZ(oz);
}

double toRadians(const double angle)
{
    return angle * (M_PI / 180);
}


void Point::rotateX(const double ox)
{
    const double cosO = cos(toRadians(ox));
    const double sinO = sin(toRadians(ox));

    const double tmp = _y;

    setY(_y * cosO + _z * sinO);
    setZ(_z * cosO - tmp * sinO);
}

void Point::rotateY(const double oy)
{
    const double cosO = cos(toRadians(oy));
    const double sinO = sin(toRadians(oy));

    const double tmp = _x;

    setX(_x * cosO + _z * sinO);
    setZ(_z * cosO - tmp * sinO);
}

void Point::rotateZ(const double oz)
{
    const double cosO = cos(toRadians(oz));
    const double sinO = sin(toRadians(oz));

    const double tmp = _x;

    setX(_x * cosO + _y * sinO);
    setY(_y * cosO - tmp * sinO);
}

