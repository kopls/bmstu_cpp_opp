#include "transform_visitor.h"

#include <cmath>

#include "list_model_structure.h"
#include "camera_impl.h"

namespace
{
double toRadians(const double angle)
{
    return angle * M_PI / 180.0;
}

void rotateVector(Point &vec, const Point &angles)
{
    double radX = toRadians(angles.getX());
    double cosX = std::cos(radX);
    double sinX = std::sin(radX);

    double y = vec.getY() * cosX - vec.getZ() * sinX;
    double z = vec.getY() * sinX + vec.getZ() * cosX;

    vec.setY(y);
    vec.setZ(z);

    double radY = toRadians(angles.getY());
    double cosY = std::cos(radY);
    double sinY = std::sin(radY);

    double x = vec.getX() * cosY + vec.getZ() * sinY;
    double z2 = vec.getZ() * cosY - vec.getX() * sinY;

    vec.setX(x);
    vec.setZ(z2);

    double radZ = toRadians(angles.getZ());
    double cosZ = std::cos(radZ);
    double sinZ = std::sin(radZ);

    double x2 = vec.getX() * cosZ - vec.getY() * sinZ;
    double y2 = vec.getX() * sinZ + vec.getY() * cosZ;

    vec.setX(x2);
    vec.setY(y2);
}
}

void TransformVisitor::visit(SkeletonModel &model)
{
    auto structure = std::static_pointer_cast<ListModelStructure>(model._modelStructure);

    structure->_center.move(_move.getX(), _move.getY(), _move.getZ());

    for (auto &point : structure->_points)
    {
        point.scale(_scale.getX(), _scale.getY(), _scale.getZ());
        point.rotate(_rotate.getX(), _rotate.getY(), _rotate.getZ());
        point.move(_move.getX(), _move.getY(), _move.getZ());
    }
}

void TransformVisitor::visit(Camera &camera)
{
    auto impl = std::static_pointer_cast<CameraImpl>(camera._impl);

    impl->_location.move(_move.getX(), _move.getY(), _move.getZ());

    rotateVector(impl->_right, _rotate);
    rotateVector(impl->_up, _rotate);
    rotateVector(impl->_forward, _rotate);

    impl->_focalLength *= _scale.getX();
}
