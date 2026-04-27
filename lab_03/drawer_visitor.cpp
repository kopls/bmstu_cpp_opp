#include "drawer_visitor.h"
#include "camera.h"
#include <iostream>

Point DrawerVisitor::getProjection(const Point& point)
{
    if (!_camera) 
        return point;
    // перевод
    double dx = point.getX() - _camera->getLocation().getX();
    double dy = point.getY() - _camera->getLocation().getY();
    double dz = point.getZ() - _camera->getLocation().getZ();
    
    // проекции
    double x = dx * _camera->getRight().getX() + dy * _camera->getRight().getY() + dz * _camera->getRight().getZ();
    double y = dx * _camera->getUp().getX() + dy * _camera->getUp().getY() + dz * _camera->getUp().getZ();
    double z = dx * _camera->getForward().getX() + dy * _camera->getForward().getY() + dz * _camera->getForward().getZ();
    
    if (z <= 0)
        return Point(0, 0, 0);
    
    double screenX = x * _camera->getFocalLength() / z;
    double screenY = y * _camera->getFocalLength() / z;
    
    screenX = (screenX + 1) * 800 / 2;
    screenY = (1 - screenY) * 600 / 2;
    
    return Point(screenX, screenY, 0);
}

void DrawerVisitor::visit(SkeletonModel &model)
{
    const auto &points = model._modelStructure->getPoints();
    const auto &edges = model._modelStructure->getEdges();

    for (const auto &edge : edges)
    {
        const auto &p1 = getProjection(points[edge.getFirst()]);
        const auto &p2 = getProjection(points[edge.getSecond()]);
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
