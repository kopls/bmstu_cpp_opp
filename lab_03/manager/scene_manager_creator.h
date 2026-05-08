#ifndef SCENE_MANAGER_CREATOR_H
#define SCENE_MANAGER_CREATOR_H

#include <memory>

#include "base_manager_creator.h"
#include "scene_manager.h"

class SceneManagerCreator : public BaseManagerCreator
{
protected:
    std::shared_ptr<BaseManager> create() override
    {
        return std::make_shared<SceneManager>();
    }
};

#endif
