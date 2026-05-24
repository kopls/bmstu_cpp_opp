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

const Point &Camera::getRight() const
{
    return _impl->getRight();
}

const Point &Camera::getUp() const
{
    return _impl->getUp();
}

const Point &Camera::getForward() const
{
    return _impl->getForward();
}

std::shared_ptr<Object> Camera::clone() const
{
    auto impl = _impl ? _impl->clone() : nullptr;
    auto camera = std::make_shared<Camera>(impl);
    camera->_id = _id;
    return camera;
}
