#include "transform_visitor.h"

void TransformVisitor::visit(SkeletonModel &model)
{
    model._modelStructure->transform(_move, _scale, _rotate);
}

void TransformVisitor::visit(Camera &camera)
{
    camera._impl->transform(_move, _scale, _rotate);
}
