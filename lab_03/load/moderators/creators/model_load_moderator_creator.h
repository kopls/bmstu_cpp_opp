#ifndef MODEL_LOAD_MODERATOR_CREATOR_H
#define MODEL_LOAD_MODERATOR_CREATOR_H

#include "base_moderator_creator.h"
#include "model_director_solution.h"
#include "model_load_moderator.h"
#include "model_builder.h"

class ModelLoadModeratorCreator : public BaseModeratorCreator<ModelLoadModerator>
{
public:
    ModelLoadModeratorCreator(ModelFileFormat format,
                              std::shared_ptr<BaseReader> reader,
                              ModelRepresentation representation)
        : _format(format), _reader(reader), _representation(representation)
    {
    }

protected:
    std::shared_ptr<ModelLoadModerator> create() override
    {
        auto builder = std::make_shared<ModelBuilder>(_representation);

        ModelDirectorSolution directorSolution;
        auto director = directorSolution.resolve(_format, _reader, builder);

        return std::make_shared<ModelLoadModerator>(director);
    }

private:
    ModelFileFormat _format;
    std::shared_ptr<BaseReader> _reader;
    ModelRepresentation _representation;
};

#endif
