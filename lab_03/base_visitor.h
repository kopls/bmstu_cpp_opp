#ifndef BASE_VISITOR_H
#define BASE_VISITOR_H

#include <memory>

class Composite;
class SkeletonModel;
class BaseCamera;

class BaseVisitor
{
public:
    virtual ~BaseVisitor() = default;

    virtual void visit(SkeletonModel &model) = 0;
    virtual void visit(Composite &composite) = 0;
    virtual void visit(BaseCamera &camera) = 0;
};

#endif
