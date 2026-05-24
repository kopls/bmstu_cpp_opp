#include "scene_memento.h"

SceneMemento::SceneMemento(std::shared_ptr<Scene> scene, std::size_t cameraId, bool hasCamera)
    : _scene(scene), _cameraId(cameraId), _hasCamera(hasCamera)
{
}

std::shared_ptr<Scene> SceneMemento::getScene() const
{
    return _scene;
}

std::size_t SceneMemento::getCameraId() const
{
    return _cameraId;
}

bool SceneMemento::hasCamera() const
{
    return _hasCamera;
}
