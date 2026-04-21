#include "drawer_visitor.h"

void Drawer_visitor::visit(SkeletonModel &model) 
{

    const auto &points = model._modelStructure.getPoints();
    const auto &edges = model._modelStructure.getEdges();

    for (const auto &edge : edges)
    {
        const auto &p1 = points[edge.getFirst()];
        const auto &p2 = points[edge.getSecond()];
        _drawer.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
}
