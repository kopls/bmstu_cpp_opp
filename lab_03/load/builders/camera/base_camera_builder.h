#ifndef BASE_CAMERA_BUILDER_H
#define BASE_CAMERA_BUILDER_H

#include <memory>

#include "base_builder.h"
#include "object.h"
#include "camera.h"
#include "point.h"

class BaseCameraBuilder : public BaseBuilder
{
public:
    BaseCameraBuilder() = default;
    ~BaseCameraBuilder() override = default;

    virtual void buildLocation(const Point &location) = 0;

    virtual std::shared_ptr<Object> getObject() = 0;
    virtual std::shared_ptr<Camera> getCamera() = 0;
};

#endif
