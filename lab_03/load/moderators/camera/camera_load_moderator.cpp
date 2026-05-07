#include "camera_load_moderator.h"

#include <stdexcept>

CameraLoadModerator::CameraLoadModerator(std::shared_ptr<BaseCameraBuildDirector> director)
    : _director(director)
{
}

std::shared_ptr<Object> CameraLoadModerator::load(const std::string &fileName)
{
    if (!_director)
        throw std::logic_error("CameraLoadModerator: director is not set");

    return _director->load(fileName);
}

void CameraLoadModerator::setDirector(std::shared_ptr<BaseCameraBuildDirector> director)
{
    _director = director;
}
