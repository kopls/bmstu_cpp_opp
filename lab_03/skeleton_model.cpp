#include "skeleton_model.h"
#include "base_visitor.h"

void SkeletonModel::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}

