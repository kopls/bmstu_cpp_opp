#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <cstddef>
#include <memory>

#include "base_manager.h"
#include "base_camera.h"
#include "scene.h"
#include "scene_memento.h"

class SceneManager : public BaseManager
{
public:
    SceneManager() = default;
    ~SceneManager() override = default;

    void setScene(std::shared_ptr<Scene> scene) { _scene = scene; }
    void setCamera(const std::size_t id)
    {
        if (!_scene)
            return;

        _camera = _scene->getCamera(id);
        if (_camera)
        {
            _cameraId = id;
            _hasCamera = true;
        }
    }

    std::shared_ptr<Scene> getScene() const { return _scene; }
    std::shared_ptr<BaseCamera> getCamera() const { return _camera; }

    SceneMemento createMemento() const
    {
        return SceneMemento(_scene ? _scene->clone() : nullptr, _cameraId, _hasCamera);
    }

    void restoreMemento(const SceneMemento &memento)
    {
        _scene = memento.getScene() ? memento.getScene()->clone() : nullptr;
        _camera.reset();
        _cameraId = memento.getCameraId();
        _hasCamera = memento.hasCamera();

        if (_scene && _hasCamera)
            _camera = _scene->getCamera(_cameraId);
    }

    std::size_t getCameraId() const { return _cameraId; }
    bool hasCamera() const { return _hasCamera; }

private:
    std::shared_ptr<Scene> _scene;
    std::shared_ptr<BaseCamera> _camera;
    std::size_t _cameraId{0};
    bool _hasCamera{false};
};

#endif
