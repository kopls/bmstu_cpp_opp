#ifndef BASE_VISITOR_H
#define BASE_VISITOR_H

#include <memory>

class BaseCamera;
class BaseDrawer;
class Composite;
class SkeletonModel;
class Camera;

class BaseVisitor
{
public:
    virtual ~BaseVisitor() = default;

    virtual void visit(SkeletonModel &model) = 0;
    virtual void visit(Composite &composite) = 0;
    virtual void visit(Camera &camera) = 0;

    virtual void setDrawer(std::shared_ptr<BaseDrawer>) {}
    virtual void setCamera(std::shared_ptr<BaseCamera>) {}
};

#endif
