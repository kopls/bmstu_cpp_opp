#include "drawer_visitor.h"
#include "camera.h"

void Camera::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}
