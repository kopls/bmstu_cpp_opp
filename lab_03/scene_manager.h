#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "base_manager.h"
#include "base_visitor.h"
#include "base_camera.h"

class SceneManager : public BaseManager
{
public:
    static std::shared_ptr<SceneManager> instance()
    {
        class SceneManagerProxy : public SceneManager {};

        static auto myInstance = std::make_shared<SceneManagerProxy>();

        return myInstance;
    }

    void setScene(std::shared_ptr<Scene> scene) { _scene = scene; }
    void setCamera(std::shared_ptr<BaseCamera> camera) { _camera = camera; }
    
    std::shared_ptr<Scene> getScene() const { return _scene; }
    std::shared_ptr<BaseCamera> getCamera() const { return _camera; }

private:
    SceneManager() = default;
    ~SceneManager() override = default;

    std::shared_ptr<Scene> _scene;
    std::shared_ptr<BaseCamera> _camera;
};

#endif
