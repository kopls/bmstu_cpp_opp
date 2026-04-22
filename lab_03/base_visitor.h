#ifndef BASE_VISITOR_H
#define BASE_VISITOR_H

class Composite;
class SkeletonModel;

class BaseVisitor
{
public:
    virtual ~BaseVisitor() = default;

    virtual void visit(SkeletonModel &model) = 0;
    virtual void visit(Composite &composite) = 0;
};

#endif
