#include "scene_load_moderator.h"

#include <stdexcept>

SceneLoadModerator::SceneLoadModerator(std::shared_ptr<BaseSceneBuildDirector> director)
    : _director(director)
{
}

std::shared_ptr<Scene> SceneLoadModerator::load(const std::string &fileName)
{
    if (!_director)
        throw std::logic_error("SceneLoadModerator: director is not set");

    return _director->load(fileName);
}

void SceneLoadModerator::setDirector(std::shared_ptr<BaseSceneBuildDirector> director)
{
    _director = director;
}
