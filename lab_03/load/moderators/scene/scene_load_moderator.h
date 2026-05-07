#ifndef SCENE_LOAD_MODERATOR_H
#define SCENE_LOAD_MODERATOR_H

#include <memory>
#include <string>

#include "base_scene_build_director.h"
#include "scene.h"

class SceneLoadModerator
{
public:
    SceneLoadModerator() = default;
    ~SceneLoadModerator() = default;
    SceneLoadModerator(std::shared_ptr<BaseSceneBuildDirector> director);

    std::shared_ptr<Scene> load(const std::string &fileName);

    void setDirector(std::shared_ptr<BaseSceneBuildDirector> director);

private:
    std::shared_ptr<BaseSceneBuildDirector> _director;
};

#endif
