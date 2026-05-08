#include <cmath>

#include "drawer_visitor.h"
#include "camera.h"

void Camera::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}

Point Camera::project(const Point &point) const
{
    return _impl->project(point);
}

const Point &Camera::getLocation() const
{
    return _impl->getLocation();
}
