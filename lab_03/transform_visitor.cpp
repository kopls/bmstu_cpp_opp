#include "transform_visitor.h"

Transformvisitor::visit(SkeletonModel &model)
{
    model->transform(_move, _scale, _rotate);
}

Transformvisitor::visit(Camera &camera)
{
    camera->transform(_move, _scale, _rotate);
}
