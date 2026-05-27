#ifndef SOLUTION_TRANSFORM_H
#define SOLUTION_TRANSFORM_H

#include <cstddef>
#include <memory>

#include "base_solution.h"
#include "point.h"
#include "scene.h"
#include "transform_manager.h"

class SolutionTransform : public BaseSolution
{
public:
    SolutionTransform() = default;
    explicit SolutionTransform(std::shared_ptr<TransformManager> manager);

    void moveSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double dx, double dy, double dz);
    void scaleSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double kx, double ky, double kz);
    void rotateSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id, double ox, double oy, double oz);
    void transformSceneObject(const std::shared_ptr<Scene> &scene, std::size_t id,
                              const Point &move, const Point &scale, const Point &rotate);

private:
    std::shared_ptr<TransformManager> _manager;
};

#endif
