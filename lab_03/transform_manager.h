#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "base_manager.h"
#include "object.h"
#include "point.h"

class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    ~TransformManager() override = default;

    static void moveObject(const std::shared_ptr<Object> &object, const double dx, const double dy, const double dz);
    static void scaleObject(const std::shared_ptr<Object> &object, const double kx, const double ky, const double kz);
    static void rotateObject(const std::shared_ptr<Object> &object, const double ox, const double oy, const double oz);
    static void transformObject(const std::shared_ptr<Object> &object, const Point &move, const Point &scale, const Point &rotate);

private:
};

#endif
