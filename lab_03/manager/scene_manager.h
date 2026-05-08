#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>

#include "base_manager.h"
#include "base_visitor.h"
#include "base_camera.h"

class SceneManager : public BaseManager
{
public:
    SceneManager() = default;
    ~SceneManager() override = default;

    void setScene(std::shared_ptr<Scene> scene) { _scene = scene; }
    void setCamera(const std::size_t id) { _camera = std::dynamic_pointer_cast<Camera>(*_scene->getObject(id)); }
    
    std::shared_ptr<Scene> getScene() const { return _scene; }
    std::shared_ptr<BaseCamera> getCamera() const { return _camera; }

private:

    std::shared_ptr<Scene> _scene;
    std::shared_ptr<BaseCamera> _camera;
};

#endif
