#ifndef BASE_MODEL_STRUCTURE_H
#define BASE_MODEL_STRUCTURE_H

#include <vector>

#include "point.h"
#include "edge.h"

class BaseModelStructure
{
public:
    ~BaseModelStructure() = default;

    virtual void addEdge(const Edge &edge) = 0;
    virtual void addPoint(const Point &point) = 0;
    virtual const std::vector<Point> &getPoints() const = 0;
    virtual const std::vector<Edge> &getEdges() const = 0;
    virtual const Point getCenter() const = 0;
};

#endif
