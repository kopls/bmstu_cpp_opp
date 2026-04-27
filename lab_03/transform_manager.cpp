#include "transform_manager.h"
#include "point.h"

void TransformManager::moveObject(const std::shared_ptr<Object> &object, const double dx, const double dy, const double dz)
{
    Point move(dx, dy, dz);
    Point scale(1, 1, 1);
    Point rotate(0, 0, 0);

    object->transform(move, scale, rotate);
}

void TransformManager::scaleObject(const std::shared_ptr<Object> &object, const double kx, const double ky, const double kz)
{
    Point move(0, 0, 0);
    Point scale(kx, ky, kz);
    Point rotate(0, 0, 0);

    object->transform(move, scale, rotate);
}

void TransformManager::rotateObject(const std::shared_ptr<Object> &object, const double ox, const double oy, const double oz)
{
    Point move(0, 0, 0);
    Point scale(1, 1, 1);
    Point rotate(ox, oy, oz);

    object->transform(move, scale, rotate);
}

void TransformManager::transformObject(const std::shared_ptr<Object> &object, const Point &move, const Point &scale, const Point &rotate)
{
    object->transform(move, scale, rotate);
}
