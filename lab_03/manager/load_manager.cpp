#include "load_manager.h"

#include <stdexcept>

#include "model_load_moderator_creator.h"
#include "reader_solution.h"

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

std::shared_ptr<Object> LoadManager::loadModel(const std::string &fileName,
                                               ModelFileFormat format,
                                               ModelRepresentation representation)
{
    ReaderSolution readerSolution;
    auto reader = readerSolution.resolve(format);

    ModelLoadModeratorCreator creator(format, reader, representation);
    auto moderator = creator.getModerator();

    return moderator->load(fileName);
}

void LoadManager::load(const std::shared_ptr<Scene> &scene, const std::string &fileName, const std::shared_ptr<std::size_t> &id)
{
    if (!scene)
        throw std::logic_error("LoadManager: scene is not set");

    scene->addObject(load(fileName), id);
}

void LoadManager::loadObjectToScene(const std::shared_ptr<Scene> &scene, const std::string &fileName, const std::shared_ptr<std::size_t> &id)
{
    load(scene, fileName, id);
}

void LoadManager::loadModelToScene(const std::shared_ptr<Scene> &scene,
                                   const std::string &fileName,
                                   ModelFileFormat format,
                                   ModelRepresentation representation,
                                   const std::shared_ptr<std::size_t> &id)
{
    if (!scene)
        throw std::logic_error("LoadManager: scene is not set");

    scene->addObject(loadModel(fileName, format, representation), id);
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
