#ifndef COMMANDS_CAMERA_COMMAND_H
#define COMMANDS_CAMERA_COMMAND_H

#include <cstddef>
#include <memory>

#include "commands/base_command.h"
#include "base_camera.h"
#include "camera.h"
#include "object.h"
#include "scene.h"
#include "scene_manager.h"
#include "transform_manager.h"


class CameraCommand : public BaseCommand
{
public:
    ~CameraCommand() override = default;
};

class AddCamera : public CameraCommand
{
    using Action = void (Scene::*)(const std::shared_ptr<Object> &);

public:
    explicit AddCamera(std::shared_ptr<Object> camera, ID id = nullptr);
    void execute() override;

private:
    Action method;
    std::shared_ptr<Object> camera;
    ID id;
};

class DeleteCamera : public CameraCommand
{
    using Action = void (Scene::*)(Iterator &);

public:
    explicit DeleteCamera(std::size_t id);
    void execute() override;

private:
    Action method;
    std::size_t id;
};

class MoveCamera : public CameraCommand
{
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

public:
    MoveCamera(std::size_t id, double dx, double dy, double dz);
    void execute() override;

private:
    Action method;
    std::size_t id;
    double dx;
    double dy;
    double dz;
};

class SetCamera : public CameraCommand
{
    using Action = void (SceneManager::*)(std::size_t);

public:
    explicit SetCamera(std::size_t id);
    void execute() override;

private:
    Action method;
    std::size_t id;
};

class GetCamera : public CameraCommand
{
    using Action = std::shared_ptr<BaseCamera> (SceneManager::*)() const;

public:
    explicit GetCamera(std::shared_ptr<BaseCamera> &camera);
    void execute() override;

private:
    Action method;
    std::shared_ptr<BaseCamera> &camera;
};

#endif
