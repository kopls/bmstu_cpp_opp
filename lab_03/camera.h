#ifndef CAMERA_H
#define CAMERA_H

#include "base_camera.h"
#include "point.h"
#include "base_visitor.h"

class Camera : public BaseCamera
{
public:
    Camera() = default;
    
    Camera(const Point &location) 
        : _location(location)
        , _right(1, 0, 0)
        , _up(0, 1, 0)
        , _forward(0, 0, 1)
        , _focalLength(1.0)
    {}

    ~Camera() override = default;

    void accept(BaseVisitor &visitor) override;
    void transform(const Point &move, const Point &scale, const Point &rotate);
    const Point &getLocation() const;
    const Point &getRight() const;
    const Point &getUp() const;
    const Point &getForward() const;
    double getFocalLength() const;


private:
    Point _location;
    Point _right;
    Point _up;
    Point _forward;
    double _focalLength;
};

#endif
