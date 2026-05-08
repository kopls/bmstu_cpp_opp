#include "transform_manager.h"
#include "point.h"

void TransformManager::moveObject(const std::shared_ptr<Object> &object, const double dx, const double dy, const double dz)
{
    transformObject(object,
                    Point(dx, dy, dz),
                    Point(1, 1, 1),
                    Point(0, 0, 0));
}

void TransformManager::scaleObject(const std::shared_ptr<Object> &object, const double kx, const double ky, const double kz)
{
    transformObject(object,
                    Point(0, 0, 0),
                    Point(kx, ky, kz),
                    Point(0, 0, 0));
}

void TransformManager::rotateObject(const std::shared_ptr<Object> &object, const double ox, const double oy, const double oz)
{
    transformObject(object,
                    Point(0, 0, 0),
                    Point(1, 1, 1),
                    Point(ox, oy, oz));
}

void TransformManager::transformObject(const std::shared_ptr<Object> &object, const Point &move, const Point &scale, const Point &rotate)
{
    _visitor->setTransform(move, scale, rotate);
    object->accept(*_visitor);
}
