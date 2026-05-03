#ifndef DRAWER_VISITOR_H
#define DRAWER_VISITOR_H

#include <memory>

#include "base_visitor.h"
#include "base_drawer.h"
#include "skeleton_model.h"
#include "composite.h"
#include "base_camera.h"
#include "point.h"

class DrawerVisitor : public BaseVisitor
{
public:
    ~DrawerVisitor() override = default;

    void visit(SkeletonModel &model) override;
    void visit(Composite &composite) override { (void)camera; };
    void visit(Camera &camera) override { (void)camera; };

    void setDrawer(std::shared_ptr<BaseDrawer> drawer) { _drawer = drawer; };
    void setCamera(std::shared_ptr<BaseCamera> camera) { _camera = camera; };
private:

    std::shared_ptr<BaseDrawer> _drawer;
    std::shared_ptr<Camera> _camera;
};

#endif
