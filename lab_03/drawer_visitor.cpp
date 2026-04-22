#include "drawer_visitor.h"

void DrawerVisitor::visit(SkeletonModel &model)
{

    const auto &points = model._modelStructure->getPoints();
    const auto &edges = model._modelStructure->getEdges();

    for (const auto &edge : edges)
    {
        const auto &p1 = points[edge.getFirst()];
        const auto &p2 = points[edge.getSecond()];
        _drawer->drawLine(p1, p2);
    }
}

void DrawerVisitor::setDrawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}
