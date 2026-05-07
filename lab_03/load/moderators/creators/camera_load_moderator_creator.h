#ifndef CAMERA_LOAD_MODERATOR_CREATOR_H
#define CAMERA_LOAD_MODERATOR_CREATOR_H

#include "base_moderator_creator.h"
#include "camera_load_moderator.h"
#include "file_camera_build_director.h"

class CameraLoadModeratorCreator : public BaseModeratorCreator<CameraLoadModerator>
{
protected:
    std::shared_ptr<CameraLoadModerator> create() override
    {
        auto director = std::make_shared<FileCameraBuildDirector>();
        return std::make_shared<CameraLoadModerator>(director);
    }
};

#endif
