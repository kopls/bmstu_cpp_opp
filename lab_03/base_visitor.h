#ifndef BASE_VISITOR_H
#define BASE_VISITOR_H

#include "skeleton_model.h"

class BaseVisitor
{
public:
    virtual ~BaseVisitor() = default;

    virtual void visit(SkeletonModel &model) = 0;
};

#endif
