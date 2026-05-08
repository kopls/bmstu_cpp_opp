#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include <memory>

#include "base_manager.h"
#include "object.h"
#include "point.h"
#include "transform_visitor.h"

class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    explicit TransformManager(std::shared_ptr<TransformVisitor> visitor) : _visitor(visitor) {}
    ~TransformManager() override = default;

    void moveObject(const std::shared_ptr<Object> &object, double dx, double dy, double dz);
    void scaleObject(const std::shared_ptr<Object> &object, double kx, double ky, double kz);
    void rotateObject(const std::shared_ptr<Object> &object, double ox, double oy, double oz);
    void transformObject(const std::shared_ptr<Object> &object, const Point &move, const Point &scale, const Point &rotate);

    void setVisitor(std::shared_ptr<TransformVisitor> visitor) { _visitor = visitor; }

private:
    std::shared_ptr<TransformVisitor> _visitor;
};

#endif
