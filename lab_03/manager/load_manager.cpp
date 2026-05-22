#include "load_manager.h"

#include <stdexcept>

LoadManager::LoadManager(std::shared_ptr<BaseLoadModerator> objectModerator,
                         std::shared_ptr<SceneLoadModerator> sceneModerator)
    : _objectModerator(objectModerator),
      _sceneModerator(sceneModerator)
{
}

std::shared_ptr<Object> LoadManager::load(const std::string &fileName)
{
    if (!_objectModerator)
        throw std::logic_error("LoadManager: object moderator is not set");

    return _objectModerator->load(fileName);
}


void LoadManager::load(const std::shared_ptr<Scene> &scene, const std::string &fileName, const std::shared_ptr<std::size_t> &id)
{
    if (!scene)
        throw std::logic_error("LoadManager: scene is not set");

    scene->addObject(load(fileName), id);
}

std::shared_ptr<Scene> LoadManager::loadScene(const std::string &fileName)
{
    if (!_sceneModerator)
        throw std::logic_error("LoadManager: scene moderator is not set");

    return _sceneModerator->load(fileName);
}

void LoadManager::setObjectModerator(std::shared_ptr<BaseLoadModerator> moderator)
{
    _objectModerator = moderator;
}

void LoadManager::setSceneModerator(std::shared_ptr<SceneLoadModerator> moderator)
{
    _sceneModerator = moderator;
}
