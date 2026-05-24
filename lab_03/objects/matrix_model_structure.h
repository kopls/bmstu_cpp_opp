#ifndef MATRIX_MODEL_STRUCTURE_H
#define MATRIX_MODEL_STRUCTURE_H

#include <vector>

#include "base_model_structure.h"
#include "edge.h"
#include "point.h"

class MatrixModelStructure : public BaseModelStructure
{
public:
    MatrixModelStructure() = default;
    MatrixModelStructure(std::vector<Point> &points, std::vector<Edge> &edges);
    MatrixModelStructure(std::vector<Point> &points, std::vector<Edge> &edges, Point &center);
    ~MatrixModelStructure() override = default;

    std::shared_ptr<BaseModelStructure> clone() const override;

    void addEdge(const Edge &edge) override;
    void addPoint(const Point &point) override;

    std::vector<Point> &getPoints() override;
    const std::vector<Point> &getPoints() const override;

    std::vector<Edge> &getEdges() override;
    const std::vector<Edge> &getEdges() const override;

    Point &getCenter() override;
    const Point getCenter() const override;

private:
    void updateEdgesCache() const;
    void revalueCenter();

    Point _center;
    std::vector<Point> _points;
    std::vector<std::vector<int>> _matrix;
    mutable std::vector<Edge> _edgesCache;
    mutable bool _cacheValid{false};
};

#endif
