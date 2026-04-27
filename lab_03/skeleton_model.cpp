#include "skeleton_model.h"
#include "base_visitor.h"

void SkeletonModel::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}

void SkeletonModel::transform(const Point &move, const Point &scale, const Point &rotate)
{
    _modelStructure->transform(move, scale, rotate);
}

