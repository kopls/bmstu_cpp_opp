#ifndef SCENE_MEMENTO_H
#define SCENE_MEMENTO_H

#include <cstddef>
#include <memory>

#include "scene.h"

class SceneMemento
{
public:
    SceneMemento() = default;
    SceneMemento(std::shared_ptr<Scene> scene, std::size_t cameraId, bool hasCamera);

    std::shared_ptr<Scene> getScene() const;
    std::size_t getCameraId() const;
    bool hasCamera() const;

private:
    std::shared_ptr<Scene> _scene;
    std::size_t _cameraId{0};
    bool _hasCamera{false};
};

#endif
