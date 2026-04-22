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

    static std::shared_ptr<DrawerVisitor> instance(std::shared_ptr<BaseDrawer> drawer = nullptr)
    {
        class DrawerVisitorProxy : public DrawerVisitor 
        {
        public:
            explicit DrawerVisitorProxy(std::shared_ptr<BaseDrawer> drawer) : DrawerVisitor(drawer) {}
        };

        static auto myInstance = std::make_shared<DrawerVisitorProxy>(drawer);

        if (drawer && myInstance)
            myInstance->setDrawer(drawer);

        return myInstance;
    }

    void setDrawer(std::shared_ptr<BaseDrawer> drawer);

    void visit(SkeletonModel &model) override;

private:
    explicit DrawerVisitor(std::shared_ptr<BaseDrawer> drawer) : _drawer(drawer) {}

    std::shared_ptr<BaseDrawer> _drawer;
    // camera
};

#endif
