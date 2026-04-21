#ifndef LIST_MODEL_STRUCTURE_H
#define LIST_MODEL_STRUCTURE_H

#include <vector>

#include "base_model_structure.h"
#include "point.h"
#include "edge.h"

class ListModelStructure : public BaseModelStructure
{
public:
    ListModelStructure() = default;
    ListModelStructure(std::vector<Point> &points, std::vector<Edge> &edges);
    ListModelStructure(std::vector<Point> &points, std::vector<Edge> &edges, Point &center);
    ~ListModelStructure() override = default;

    void addEdge(const Edge &edge) override;
    void addPoint(const Point &point) override;

    const std::vector<Point> &getPoints() const override;
    const std::vector<Edge> &getEdges() const override;
    const Point getCentre() const override;

private:
    Point _center;
    std::vector<Point> _points;
    std::vector<Edge> _edges;
};

#endif
