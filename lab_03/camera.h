#ifndef CAMERA_H
#define CAMERA_H

#include "base_camera.h"
#include "point.h"
#include "drawer_visitor.h"

class Camera : public BaseCamera
{
public:
    Camera() = default;
    
    Camera(const Point &location) 
        : location(location)
        , right(1, 0, 0)
        , up(0, 1, 0)
        , forward(0, 0, 1)
    {}

    ~Camera() override = default;

    void accept(BaseVisitor &visitor) override;

    double focalLength;
    Point location;
    Point right;
    Point up;
    Point forward;
};

#endif
