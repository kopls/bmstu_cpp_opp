#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include <memory>
#include <string>

#include "base_manager.h"
#include "object.h"
#include "scene.h"
#include "base_load_moderator.h"
#include "scene_load_moderator.h"

class LoadManager : public BaseManager
{
public:
    LoadManager() = default;
    LoadManager(std::shared_ptr<BaseLoadModerator> objectModerator,
                std::shared_ptr<SceneLoadModerator> sceneModerator);
    ~LoadManager() override = default;

    std::shared_ptr<Object> load(const std::string &fileName);
    std::shared_ptr<Scene> loadScene(const std::string &fileName);

    void setObjectModerator(std::shared_ptr<BaseLoadModerator> moderator);
    void setSceneModerator(std::shared_ptr<SceneLoadModerator> moderator);

private:
    std::shared_ptr<BaseLoadModerator> _objectModerator;
    std::shared_ptr<SceneLoadModerator> _sceneModerator;
};

#endif
