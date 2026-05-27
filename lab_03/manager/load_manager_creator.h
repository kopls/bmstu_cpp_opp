#ifndef LOAD_MANAGER_CREATOR_H
#define LOAD_MANAGER_CREATOR_H

#include <memory>

#include "base_manager_creator.h"
#include "load_manager.h"
#include "model_load_moderator_creator.h"
#include "scene_load_moderator_creator.h"

class LoadManagerCreator : public BaseManagerCreator<LoadManager>
{
protected:
    std::shared_ptr<LoadManager> create() override
    {
        return std::make_shared<LoadManager>();
    }
};

#endif
