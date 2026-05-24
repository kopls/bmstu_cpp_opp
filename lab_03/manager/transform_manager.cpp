#include "transform_manager.h"
#include "point.h"

#include <stdexcept>

namespace
{
std::shared_ptr<Object> getObjectOrThrow(const std::shared_ptr<Scene> &scene, std::size_t id)
{
    if (!scene)
        throw std::logic_error("TransformManager: scene is not set");

    auto iter = scene->getObject(id);

    if (iter == scene->end())
        throw std::logic_error("TransformManager: object not found");

    return *iter;
}
}

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
    if (!_visitor)
        throw std::logic_error("TransformManager: visitor is not set");

    if (!object)
        throw std::logic_error("TransformManager: object is not set");

    _visitor->setTransform(move, scale, rotate);
    object->accept(*_visitor);
}

void TransformManager::moveObject(const std::shared_ptr<Scene> &scene, std::size_t id, double dx, double dy, double dz)
{
    moveObject(getObjectOrThrow(scene, id), dx, dy, dz);
}

void TransformManager::scaleObject(const std::shared_ptr<Scene> &scene, std::size_t id, double kx, double ky, double kz)
{
    scaleObject(getObjectOrThrow(scene, id), kx, ky, kz);
}

void TransformManager::rotateObject(const std::shared_ptr<Scene> &scene, std::size_t id, double ox, double oy, double oz)
{
    rotateObject(getObjectOrThrow(scene, id), ox, oy, oz);
}

void TransformManager::transformObject(const std::shared_ptr<Scene> &scene, std::size_t id, const Point &move, const Point &scale, const Point &rotate)
{
    transformObject(getObjectOrThrow(scene, id), move, scale, rotate);
}

void TransformManager::moveSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double dx, double dy, double dz)
{
    moveObject(scene, id, dx, dy, dz);
}

void TransformManager::scaleSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double kx, double ky, double kz)
{
    scaleObject(scene, id, kx, ky, kz);
}

void TransformManager::rotateSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double ox, double oy, double oz)
{
    rotateObject(scene, id, ox, oy, oz);
}

void TransformManager::transformSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, const Point &move, const Point &scale, const Point &rotate)
{
    transformObject(scene, id, move, scale, rotate);
}
