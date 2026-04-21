#ifndef DRAWER_VISITOR_H
#define DRAWER_VISITOR_H

#include <memory>

#include "base_visitor.h"
#include "base_drawer.h"
#include "skeleton_model.h"

class DrawerVisitor : public BaseVisitor
{
public:
    ~DrawerVisitor() override = default;
    explicit DrawerVisitor(std::shared_ptr<BaseDrawer> drawer) : _drawer(drawer) {}

    void visit(SkeletonModel &model) override;

private:
    std::shared_ptr<BaseDrawer> _drawer;
};

#endif
