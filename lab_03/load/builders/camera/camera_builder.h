#ifndef CAMERA_BUILDER_H
#define CAMERA_BUILDER_H

#include <memory>

#include "base_camera_builder.h"
#include "base_camera_impl.h"

class CameraBuilder : public BaseCameraBuilder
{
public:
    CameraBuilder() = default;
    ~CameraBuilder() override = default;

    void build() override;
    void buildLocation(const Point &location) override;
    bool isBuild() const override;

    std::shared_ptr<Object> getObject() override;
    std::shared_ptr<Camera> getCamera() override;

private:
    std::shared_ptr<BaseCameraImpl> _impl;
};

#endif
