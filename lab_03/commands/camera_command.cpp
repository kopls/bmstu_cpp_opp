#include "commands/camera_command.h"

#include <stdexcept>

namespace
{
std::shared_ptr<Scene> getSceneOrThrow(const std::shared_ptr<SceneManager> &sceneManager, const char *message)
{
    if (!sceneManager || !sceneManager->getScene())
        throw std::logic_error(message);

    return sceneManager->getScene();
}
}

AddCamera::AddCamera(std::shared_ptr<SceneManager> sceneManager,
                     ID id,
                     double x,
                     double y,
                     double z,
                     Action action)
    : _sceneManager(sceneManager),
      _action(action),
      _id(id),
      _x(x),
      _y(y),
      _z(z)
{
}

void AddCamera::execute()
{
    auto scene = getSceneOrThrow(_sceneManager, "AddCamera: scene is not set");

    auto impl = std::make_shared<CameraImpl>(Point(_x, _y, _z));
    auto camera = std::make_shared<Camera>(impl);

    ((*scene).*_action)(camera);

    if (_id)
        *_id = camera->getId();
}

DeleteCamera::DeleteCamera(std::shared_ptr<SceneManager> sceneManager,
                           std::size_t id,
                           Action action)
    : _sceneManager(sceneManager),
      _action(action),
      _id(id)
{
}

void DeleteCamera::execute()
{
    auto scene = getSceneOrThrow(_sceneManager, "DeleteCamera: scene is not set");
    auto iter = scene->getObject(_id);

    if (iter == scene->end())
        throw std::logic_error("DeleteCamera: camera not found");

    ((*scene).*_action)(iter);
}

MoveCamera::MoveCamera(std::shared_ptr<SceneManager> sceneManager,
                       std::shared_ptr<TransformManager> transformManager,
                       std::size_t id,
                       double dx,
                       double dy,
                       double dz,
                       Action action)
    : _sceneManager(sceneManager),
      _receiver(transformManager),
      _action(action),
      _id(id),
      _dx(dx),
      _dy(dy),
      _dz(dz)
{
}

void MoveCamera::execute()
{
    auto scene = getSceneOrThrow(_sceneManager, "MoveCamera: scene is not set");
    auto iter = scene->getObject(_id);

    if (iter == scene->end())
        throw std::logic_error("MoveCamera: camera not found");

    auto object = *iter;
    ((*_receiver).*_action)(object, _dx, _dy, _dz);
}

SetCamera::SetCamera(std::shared_ptr<SceneManager> sceneManager,
                     std::size_t id,
                     Action action)
    : _receiver(sceneManager),
      _action(action),
      _id(id)
{
}

void SetCamera::execute()
{
    ((*_receiver).*_action)(_id);
}
