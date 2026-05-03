#ifndef TRANSFORM_VISITOR_H
#define TRANSFORM_VISITOR_H

#include <memory>

#include "base_visitor.h"
#include "skeleton_model.h"
#include "composite.h"
#include "camera.h"
#include "point.h"

class TransformVisitor : public BaseVisitor
{
public:
    ~TransformVisitor() override = default;

    void visit(SkeletonModel &model) override;
    void visit(Composite &composite) override { (void)camera; };
    void visit(Camera &camera) override;
    void setTransform(const Point &move, const Point &scale, const Point &rotate) : _move(move), _scale(scale), _rotate(rotate) {}

private:
    Point _move;
    Point _scale;
    Point _rotate;
};

#endif
