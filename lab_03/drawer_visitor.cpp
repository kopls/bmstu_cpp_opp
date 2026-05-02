#include "drawer_visitor.h"
#include "camera.h"
#include <iostream>

void DrawerVisitor::visit(SkeletonModel &model)
{
    const auto &points = model._modelStructure->getPoints();
    const auto &edges = model._modelStructure->getEdges();

    for (const auto &edge : edges)
    {
        const auto &p1 = _camera->project(points[edge.getFirst()]);
        const auto &p2 = _camera->project(points[edge.getSecond()]);
        _drawer->drawLine(p1, p2);
    }
}

void DrawerVisitor::visit(Composite &composite)
{
    for (const auto &elem : composite.getElements())
        elem->accept(*this);
}

void DrawerVisitor::setDrawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}

void DrawerVisitor::setCamera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}
