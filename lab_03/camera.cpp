#include "drawer_visitor.h"
#include "camera.h"

void Camera::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}

void Camera::moveX(const double dx)
{
    _location.setX(_location.getX() + dx);
}

void Camera::moveY(const double dy)
{
    _location.setY(_location.getY() + dy);
}

void Camera::moveZ(const double dz)
{
    _location.setZ(_location.getZ() + dz);
}

