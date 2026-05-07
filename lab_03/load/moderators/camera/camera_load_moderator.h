#ifndef CAMERA_LOAD_MODERATOR_H
#define CAMERA_LOAD_MODERATOR_H

#include <memory>

#include "../base_load_moderator.h"
#include "../../directors/camera/base_camera_build_director.h"

class CameraLoadModerator : public BaseLoadModerator
{
public:
    CameraLoadModerator() = default;
    explicit CameraLoadModerator(std::shared_ptr<BaseCameraBuildDirector> director);
    ~CameraLoadModerator() override = default;

    std::shared_ptr<Object> load(const std::string &fileName) override;

    void setDirector(std::shared_ptr<BaseCameraBuildDirector> director);

private:
    std::shared_ptr<BaseCameraBuildDirector> _director;
};

#endif
