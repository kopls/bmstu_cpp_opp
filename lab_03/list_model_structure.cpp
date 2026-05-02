
#include "list_model_structure.h"

ListModelStructure::ListModelStructure(std::vector<Point> &points, std::vector<Edge> &edges) : _center{}, _points(points), _edges(edges)
{

};

ListModelStructure::ListModelStructure(std::vector<Point> &points, std::vector<Edge> &edges, Point &center) : _center(center), _points(points), _edges(edges)
{

};

void ListModelStructure::addEdge(const Edge &edge)
{
    _edges.push_back(edge);
}

void ListModelStructure::addPoint(const Point &point)
{
    _points.push_back(point);
}

const std::vector<Point> &ListModelStructure::getPoints() const 
{
    return _points;
}

const std::vector<Edge> &ListModelStructure::getEdges() const
{
    return _edges;
}

const Point ListModelStructure::getCenter() const
{
    return _center;
}

void ListModelStructure::transform(const Point &move, const Point &scale, const Point &rotate)
{
   _center.move(move.getX(), move.getY(), move.getZ());

   for (auto &point : _points)
   {
        point.scale(scale.getX(), scale.getY(), scale.getZ());
        point.rotate(rotate.getX(), rotate.getY(), rotate.getZ());
        point.move(move.getX(), move.getY(), move.getZ());
   }
}
