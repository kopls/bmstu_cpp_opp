#include "solution_transform.h"

#include <stdexcept>

SolutionTransform::SolutionTransform(std::shared_ptr<TransformManager> manager)
    : _manager(manager)
{
}

void SolutionTransform::moveSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double dx, double dy, double dz)
{
    if (!_manager)
        throw std::logic_error("SolutionTransform: manager is not set");

    _manager->moveSceneObject(scene, id, dx, dy, dz);
}

void SolutionTransform::scaleSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double kx, double ky, double kz)
{
    if (!_manager)
        throw std::logic_error("SolutionTransform: manager is not set");

    _manager->scaleSceneObject(scene, id, kx, ky, kz);
}

void SolutionTransform::rotateSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double ox, double oy, double oz)
{
    if (!_manager)
        throw std::logic_error("SolutionTransform: manager is not set");

    _manager->rotateSceneObject(scene, id, ox, oy, oz);
}

void SolutionTransform::transformSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id,
                                             const Point &move, const Point &scale, const Point &rotate)
{
    if (!_manager)
        throw std::logic_error("SolutionTransform: manager is not set");

    _manager->transformSceneObject(scene, id, move, scale, rotate);
}
