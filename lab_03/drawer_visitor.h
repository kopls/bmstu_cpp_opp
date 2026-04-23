#ifndef DRAWER_VISITOR_H
#define DRAWER_VISITOR_H

#include <memory>

#include "base_visitor.h"
#include "base_drawer.h"
#include "skeleton_model.h"
#include "composite.h"
#include "camera.h"
#include "point.h"

class DrawerVisitor : public BaseVisitor
{
public:
    ~DrawerVisitor() override = default;

    static std::shared_ptr<DrawerVisitor> instance(std::shared_ptr<BaseDrawer> drawer = nullptr, std::shared_ptr<Camera> camera = nullptr)
    {
        class DrawerVisitorProxy : public DrawerVisitor 
        {
        public:
            explicit DrawerVisitorProxy(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<Camera> camera) : DrawerVisitor(drawer, camera) {}
        };

        static auto myInstance = std::make_shared<DrawerVisitorProxy>(drawer, camera);

        if (drawer && myInstance)
            myInstance->setDrawer(drawer);

        if (camera && myInstance)
            myInstance->setCamera(camera);

        return myInstance;
    }

    Point getProjection(const Point &point);

    void setDrawer(std::shared_ptr<BaseDrawer> drawer);
    void setCamera(std::shared_ptr<Camera> camera);

    void visit(SkeletonModel &model) override;
    void visit(Composite &composite) override;
    void visit(Camera &camera) override {};

private:
    explicit DrawerVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<Camera> camera) : _drawer(drawer), _camera(camera) {}

    std::shared_ptr<BaseDrawer> _drawer;
    std::shared_ptr<Camera> _camera;
};

#endif
