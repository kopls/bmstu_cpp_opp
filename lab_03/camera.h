#ifndef CAMERA_H
#define CAMERA_H

#include "base_camera.h"
#include "point.h"
#include "drawer_visitor.h"

class Camera : public BaseCamera
{
public:
    Camera() = default;
    Camera(const Point &location) : _location(location) {}
    ~Camera() override = default;

    void accept(BaseVisitor &visitor) override;

private:
    void moveX(const double dx);
    void moveY(const double dy);
    void moveZ(const double dz);

    Point _location;
};

#endif
