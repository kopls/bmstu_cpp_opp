#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include "base_camera_impl.h"
#include "base_camera.h"
#include "point.h"
#include "base_visitor.h"

class Camera : public BaseCamera
{
public:
    Camera() = default;
    
    Camera(std::shared_ptr<BaseCameraImpl> impl) : _impl(impl) {}

    ~Camera() override = default;

    void accept(BaseVisitor &visitor) override;
    Point project(const Point &point) const;
    const Point &getLocation() const;

//private: дружба крепкая
    std::shared_ptr<BaseCameraImpl> _impl;
};

#endif
