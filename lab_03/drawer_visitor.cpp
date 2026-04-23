#include "drawer_visitor.h"
#include "camera.h"

Point DrawerVisitor::getProjection(const Point& point)
{
    if (!_camera) 
        return point;
    // перевод
    double dx = point.getX() - _camera->location.getX();
    double dy = point.getY() - _camera->location.getY();
    double dz = point.getZ() - _camera->location.getZ();
    
    // проекции
    double x = dx * _camera->right.getX() + dy * _camera->right.getY() + dz * _camera->right.getZ();
    double y = dx * _camera->up.getX() + dy * _camera->up.getY() + dz * _camera->up.getZ();
    double z = dx * _camera->forward.getX() + dy * _camera->forward.getY() + dz * _camera->forward.getZ();
    
    if (z <= 0)
        return Point(0, 0, 0);
    
    double screenX = x * _camera->focalLength / z;
    double screenY = y * _camera->focalLength / z;
    
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
