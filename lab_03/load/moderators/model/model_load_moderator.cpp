#include "model_load_moderator.h"

#include <stdexcept>

ModelLoadModerator::ModelLoadModerator(std::shared_ptr<BaseModelBuildDirector> director)
    : _director(director)
{
}

std::shared_ptr<Object> ModelLoadModerator::load(const std::string &fileName)
{
    if (!_director)
        throw std::logic_error("ModelLoadModerator: director is not set");

    return _director->load(fileName);
}

void ModelLoadModerator::setDirector(std::shared_ptr<BaseModelBuildDirector> director)
{
    _director = director;
}
