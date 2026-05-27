#ifndef MODEL_LOAD_MODERATOR_CREATOR_H
#define MODEL_LOAD_MODERATOR_CREATOR_H

#include "base_moderator_creator.h"
#include "model_load_moderator.h"
#include "file_model_build_director.h"

class ModelLoadModeratorCreator : public BaseModeratorCreator<ModelLoadModerator>
{
public:
    ModelLoadModeratorCreator(std::shared_ptr<BaseReader> reader,
                              ModelRepresentation representation)
        : _reader(reader), _representation(representation)
    {
    }

protected:
    std::shared_ptr<ModelLoadModerator> create() override
    {
        auto builder = std::make_shared<ModelBuilder>(_representation);
        auto director = std::make_shared<FileModelBuildDirector>(_reader, builder);

        return std::make_shared<ModelLoadModerator>(director);
    }

private:
    std::shared_ptr<BaseReader> _reader;
    ModelRepresentation _representation;
};

#endif
