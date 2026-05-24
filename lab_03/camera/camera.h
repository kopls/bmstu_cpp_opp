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
    std::shared_ptr<Object> clone() const override;
    Point project(const Point &point) const override;
    const Point &getLocation() const override;
    const Point &getRight() const override;
    const Point &getUp() const override;
    const Point &getForward() const override;

//private:
    std::shared_ptr<BaseCameraImpl> _impl;
};

#endif
