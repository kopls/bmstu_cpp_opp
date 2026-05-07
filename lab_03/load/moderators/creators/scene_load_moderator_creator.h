#ifndef SCENE_LOAD_MODERATOR_CREATOR_H
#define SCENE_LOAD_MODERATOR_CREATOR_H

#include "base_moderator_creator.h"
#include "scene_load_moderator.h"
#include "file_scene_build_director.h"

class SceneLoadModeratorCreator : public BaseModeratorCreator<SceneLoadModerator>
{
protected:
    std::shared_ptr<SceneLoadModerator> create() override
    {
        auto director = std::make_shared<FileSceneBuildDirector>();
        return std::make_shared<SceneLoadModerator>(director);
    }
};

#endif
