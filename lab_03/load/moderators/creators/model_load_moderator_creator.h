#ifndef MODEL_LOAD_MODERATOR_CREATOR_H
#define MODEL_LOAD_MODERATOR_CREATOR_H

#include "base_moderator_creator.h"
#include "model_load_moderator.h"
#include "file_model_build_director.h"

class ModelLoadModeratorCreator : public BaseModeratorCreator<ModelLoadModerator>
{
protected:
    std::shared_ptr<ModelLoadModerator> create() override
    {
        auto director = std::make_shared<FileModelBuildDirector>();
        return std::make_shared<ModelLoadModerator>(director);
    }
};

#endif
