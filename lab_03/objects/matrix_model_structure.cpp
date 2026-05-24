#include "matrix_model_structure.h"

#include <memory>
#include <stdexcept>

MatrixModelStructure::MatrixModelStructure(std::vector<Point> &points, std::vector<Edge> &edges)
    : _points(points)
{
    for (std::size_t i = 0; i < _points.size(); ++i)
        _matrix.emplace_back(_points.size(), 0);

    for (const auto &edge : edges)
        addEdge(edge);

    revalueCenter();
}

MatrixModelStructure::MatrixModelStructure(std::vector<Point> &points, std::vector<Edge> &edges, Point &center)
    : _center(center), _points(points)
{
    for (std::size_t i = 0; i < _points.size(); ++i)
        _matrix.emplace_back(_points.size(), 0);

    for (const auto &edge : edges)
        addEdge(edge);
}

std::shared_ptr<BaseModelStructure> MatrixModelStructure::clone() const
{
    return std::make_shared<MatrixModelStructure>(*this);
}

void MatrixModelStructure::addPoint(const Point &point)
{
    _points.push_back(point);

    for (auto &row : _matrix)
        row.push_back(0);

    _matrix.emplace_back(_points.size(), 0);
    _cacheValid = false;
    revalueCenter();
}

void MatrixModelStructure::addEdge(const Edge &edge)
{
    const std::size_t first = edge.getFirst();
    const std::size_t second = edge.getSecond();

    if (first >= _points.size() || second >= _points.size())
        throw std::logic_error("MatrixModelStructure: edge index is out of range");

    _matrix[first][second] = 1;
    _matrix[second][first] = 1;
    _cacheValid = false;
}

std::vector<Point> &MatrixModelStructure::getPoints()
{
    return _points;
}

const std::vector<Point> &MatrixModelStructure::getPoints() const
{
    return _points;
}

std::vector<Edge> &MatrixModelStructure::getEdges()
{
    updateEdgesCache();
    return _edgesCache;
}

const std::vector<Edge> &MatrixModelStructure::getEdges() const
{
    updateEdgesCache();
    return _edgesCache;
}

Point &MatrixModelStructure::getCenter()
{
    return _center;
}

const Point MatrixModelStructure::getCenter() const
{
    return _center;
}

void MatrixModelStructure::updateEdgesCache() const
{
    if (_cacheValid)
        return;

    _edgesCache.clear();

    for (std::size_t i = 0; i < _matrix.size(); ++i)
        for (std::size_t j = i + 1; j < _matrix[i].size(); ++j)
            if (_matrix[i][j] != 0)
                _edgesCache.emplace_back(i, j);

    _cacheValid = true;
}

void MatrixModelStructure::revalueCenter()
{
    if (_points.empty())
    {
        _center = Point(0, 0, 0);
        return;
    }

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    for (const auto &point : _points)
    {
        x += point.getX();
        y += point.getY();
        z += point.getZ();
    }

    const double count = _points.size();
    _center = Point(x / count, y / count, z / count);
}
