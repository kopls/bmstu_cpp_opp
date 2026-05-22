
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

std::vector<Point> &ListModelStructure::getPoints()
{
    return _points;
}

const std::vector<Point> &ListModelStructure::getPoints() const 
{
    return _points;
}

std::vector<Edge> &ListModelStructure::getEdges()
{
    return _edges;
}

const std::vector<Edge> &ListModelStructure::getEdges() const
{
    return _edges;
}

Point &ListModelStructure::getCenter()
{
    return _center;
}

const Point ListModelStructure::getCenter() const
{
    return _center;
}
