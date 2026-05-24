#ifndef BASE_MODEL_STRUCTURE_H
#define BASE_MODEL_STRUCTURE_H

#include <memory>
#include <vector>

#include "point.h"
#include "edge.h"

class BaseModelStructure
{
public:
    virtual ~BaseModelStructure() = default;

    virtual std::shared_ptr<BaseModelStructure> clone() const = 0;

    virtual void addEdge(const Edge &edge) = 0;
    virtual void addPoint(const Point &point) = 0;

    virtual std::vector<Point> &getPoints() = 0;
    virtual const std::vector<Point> &getPoints() const = 0;

    virtual std::vector<Edge> &getEdges() = 0;
    virtual const std::vector<Edge> &getEdges() const = 0;

    virtual Point &getCenter() = 0;
    virtual const Point getCenter() const = 0;
};

#endif
