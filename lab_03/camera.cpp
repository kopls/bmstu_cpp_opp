#include <cmath>

#include "drawer_visitor.h"
#include "camera.h"

void Camera::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}

void Camera::transform(const Point &move, const Point &scale, const Point &rotate)
{
    _impl->transform(move, scale, rotate);
}

Point Camera::project(const Point &point) const
{
    return _impl->project(point);
}

const Point &Camera::getLocation() const
{
    return _impl->getLocation();
}
