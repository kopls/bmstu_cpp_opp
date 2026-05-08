#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include <cstddef>
#include <memory>

#include "commands/base_command.h"
#include "object.h"
#include "point.h"
#include "scene_manager.h"
#include "scene.h"
#include "transform_manager.h"

class ModelCommand : public BaseCommand
{
public:
    ~ModelCommand() override = default;
};

class MoveModel : public ModelCommand
{
public:
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

    MoveModel(std::shared_ptr<SceneManager> sceneManager,
              std::shared_ptr<TransformManager> transformManager,
              std::size_t id,
              double dx,
              double dy,
              double dz,
              Action action = &TransformManager::moveObject);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _receiver;
    Action _action;

    std::size_t _id;
    double _dx;
    double _dy;
    double _dz;
};

class ScaleModel : public ModelCommand
{
public:
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

    ScaleModel(std::shared_ptr<SceneManager> sceneManager,
               std::shared_ptr<TransformManager> transformManager,
               std::size_t id,
               double kx,
               double ky,
               double kz,
               Action action = &TransformManager::scaleObject);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _receiver;
    Action _action;

    std::size_t _id;
    double _kx;
    double _ky;
    double _kz;
};

class RotateModel : public ModelCommand
{
public:
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

    RotateModel(std::shared_ptr<SceneManager> sceneManager,
                std::shared_ptr<TransformManager> transformManager,
                std::size_t id,
                double ox,
                double oy,
                double oz,
                Action action = &TransformManager::rotateObject);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _receiver;
    Action _action;

    std::size_t _id;
    double _ox;
    double _oy;
    double _oz;
};

class TransformModel : public ModelCommand
{
public:
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, const Point &, const Point &, const Point &);

    TransformModel(std::shared_ptr<SceneManager> sceneManager,
                   std::shared_ptr<TransformManager> transformManager,
                   std::size_t id,
                   const Point &move,
                   const Point &scale,
                   const Point &rotate,
                   Action action = &TransformManager::transformObject);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _receiver;
    Action _action;

    std::size_t _id;
    Point _move;
    Point _scale;
    Point _rotate;
};

class DeleteModel : public ModelCommand
{
public:
    using Action = void (Scene::*)(Iterator &);

    DeleteModel(std::shared_ptr<SceneManager> sceneManager,
                std::size_t id,
                Action action = &Scene::deleteObject);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    Action _action;

    std::size_t _id;
};

#endif
