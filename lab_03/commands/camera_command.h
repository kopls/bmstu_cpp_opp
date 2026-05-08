#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include <cstddef>
#include <memory>

#include "commands/base_command.h"
#include "camera.h"
#include "camera_impl.h"
#include "object.h"
#include "point.h"
#include "scene.h"
#include "scene_manager.h"
#include "transform_manager.h"

using ID = std::shared_ptr<std::size_t>;

class CameraCommand : public BaseCommand
{
public:
    ~CameraCommand() override = default;
};

class AddCamera : public CameraCommand
{
public:
    using Action = void (Scene::*)(const std::shared_ptr<Object> &);

    AddCamera(std::shared_ptr<SceneManager> sceneManager,
              ID id,
              double x,
              double y,
              double z,
              Action action = &Scene::addObject);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    Action _action;

    ID _id;
    double _x;
    double _y;
    double _z;
};

class DeleteCamera : public CameraCommand
{
public:
    using Action = void (Scene::*)(Iterator &);

    DeleteCamera(std::shared_ptr<SceneManager> sceneManager,
                 std::size_t id,
                 Action action = &Scene::deleteObject);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _sceneManager;
    Action _action;

    std::size_t _id;
};

class MoveCamera : public CameraCommand
{
public:
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

    MoveCamera(std::shared_ptr<SceneManager> sceneManager,
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

class SetCamera : public CameraCommand
{
public:
    using Action = void (SceneManager::*)(std::size_t);

    SetCamera(std::shared_ptr<SceneManager> sceneManager,
              std::size_t id,
              Action action = &SceneManager::setCamera);

    void execute() override;

private:
    std::shared_ptr<SceneManager> _receiver;
    Action _action;

    std::size_t _id;
};

#endif
