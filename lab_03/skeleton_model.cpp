#include "skeleton_model.h"

void SkeletonModel::accept(Visitor &visitor)
{
    visitor.visit(*this);
}




