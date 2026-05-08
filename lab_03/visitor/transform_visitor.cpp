#include "transform_visitor.h"

TransformVisitor::visit(SkeletonModel &model)
{
    model.modelStructure->transform(_move, _scale, _rotate);
}

TransformVisitor::visit(Camera &camera)
{
    camera._impl->transform(_move, _scale, _rotate);
}
