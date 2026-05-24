#include "drawer_visitor.h"
#include "camera.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <limits>
#include <set>
#include <vector>

namespace
{
constexpr double NEAR_PLANE = 1.0;
constexpr double EPS = 1e-9;
constexpr double DEPTH_EPS = 1e-4;
constexpr double SCREEN_WIDTH = 800.0;
constexpr double SCREEN_HEIGHT = 600.0;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

using Face = std::vector<std::size_t>;

double dot(const Point &left, const Point &right)
{
    return left.getX() * right.getX() + left.getY() * right.getY() + left.getZ() * right.getZ();
}

Point subtract(const Point &left, const Point &right)
{
    return Point(left.getX() - right.getX(),
                 left.getY() - right.getY(),
                 left.getZ() - right.getZ());
}

Point cross(const Point &left, const Point &right)
{
    return Point(left.getY() * right.getZ() - left.getZ() * right.getY(),
                 left.getZ() * right.getX() - left.getX() * right.getZ(),
                 left.getX() * right.getY() - left.getY() * right.getX());
}

double length(const Point &point)
{
    return std::sqrt(dot(point, point));
}

Point interpolate(const Point &first, const Point &second, const double t)
{
    return Point(first.getX() + (second.getX() - first.getX()) * t,
                 first.getY() + (second.getY() - first.getY()) * t,
                 first.getZ() + (second.getZ() - first.getZ()) * t);
}

Point relativeToCamera(const Point &point, const BaseCamera &camera)
{
    return Point(point.getX() - camera.getLocation().getX(),
                 point.getY() - camera.getLocation().getY(),
                 point.getZ() - camera.getLocation().getZ());
}

double cameraDepth(const Point &point, const BaseCamera &camera)
{
    return dot(relativeToCamera(point, camera), camera.getForward());
}

bool isFinitePoint(const Point &point)
{
    return std::isfinite(point.getX()) &&
           std::isfinite(point.getY()) &&
           std::isfinite(point.getZ());
}

int outCode(double x, double y)
{
    int code = INSIDE;

    if (x < 0.0)
        code |= LEFT;
    else if (x > SCREEN_WIDTH)
        code |= RIGHT;

    if (y < 0.0)
        code |= TOP;
    else if (y > SCREEN_HEIGHT)
        code |= BOTTOM;

    return code;
}

bool clipLine(Point &first, Point &second)
{
    double x1 = first.getX();
    double y1 = first.getY();
    double x2 = second.getX();
    double y2 = second.getY();

    int code1 = outCode(x1, y1);
    int code2 = outCode(x2, y2);

    while (true)
    {
        if ((code1 | code2) == 0)
        {
            first.setX(x1);
            first.setY(y1);
            second.setX(x2);
            second.setY(y2);
            return true;
        }

        if ((code1 & code2) != 0)
            return false;

        const int code = code1 != 0 ? code1 : code2;
        double x = 0.0;
        double y = 0.0;

        if ((code & TOP) != 0)
        {
            if (std::abs(y2 - y1) < EPS)
                return false;

            x = x1 + (x2 - x1) * (0.0 - y1) / (y2 - y1);
            y = 0.0;
        }
        else if ((code & BOTTOM) != 0)
        {
            if (std::abs(y2 - y1) < EPS)
                return false;

            x = x1 + (x2 - x1) * (SCREEN_HEIGHT - y1) / (y2 - y1);
            y = SCREEN_HEIGHT;
        }
        else if ((code & RIGHT) != 0)
        {
            if (std::abs(x2 - x1) < EPS)
                return false;

            y = y1 + (y2 - y1) * (SCREEN_WIDTH - x1) / (x2 - x1);
            x = SCREEN_WIDTH;
        }
        else if ((code & LEFT) != 0)
        {
            if (std::abs(x2 - x1) < EPS)
                return false;

            y = y1 + (y2 - y1) * (0.0 - x1) / (x2 - x1);
            x = 0.0;
        }

        if (code == code1)
        {
            x1 = x;
            y1 = y;
            code1 = outCode(x1, y1);
        }
        else
        {
            x2 = x;
            y2 = y;
            code2 = outCode(x2, y2);
        }
    }
}

Face canonicalFace(const Face &face)
{
    std::vector<Face> variants;
    variants.reserve(face.size() * 2);

    Face direct = face;
    Face reversed = face;
    std::reverse(reversed.begin(), reversed.end());

    for (std::size_t i = 0; i < face.size(); ++i)
    {
        std::rotate(direct.begin(), direct.begin() + 1, direct.end());
        variants.push_back(direct);

        std::rotate(reversed.begin(), reversed.begin() + 1, reversed.end());
        variants.push_back(reversed);
    }

    return *std::min_element(variants.begin(), variants.end());
}

bool isPlanarFace(const Face &face, const std::vector<Point> &points)
{
    if (face.size() < 3)
        return false;

    const Point first = subtract(points[face[1]], points[face[0]]);
    const Point second = subtract(points[face[2]], points[face[0]]);
    const Point normal = cross(first, second);
    const double normalLength = length(normal);

    if (normalLength < EPS)
        return false;

    for (std::size_t i = 3; i < face.size(); ++i)
    {
        const Point current = subtract(points[face[i]], points[face[0]]);

        if (std::abs(dot(current, normal)) > normalLength * 1e-5)
            return false;
    }

    return true;
}

bool hasVertex(const Face &face, const std::size_t vertex)
{
    return std::find(face.begin(), face.end(), vertex) != face.end();
}

bool faceHasEdge(const Face &face, const Edge &edge)
{
    if (!hasVertex(face, edge.getFirst()) || !hasVertex(face, edge.getSecond()))
        return false;

    for (std::size_t i = 0; i < face.size(); ++i)
    {
        const std::size_t first = face[i];
        const std::size_t second = face[(i + 1) % face.size()];

        if ((first == edge.getFirst() && second == edge.getSecond()) ||
            (first == edge.getSecond() && second == edge.getFirst()))
            return true;
    }

    return false;
}

std::vector<Face> buildFaces(const std::vector<Point> &points, const std::vector<Edge> &edges)
{
    std::vector<std::vector<std::size_t>> graph(points.size());

    for (const auto &edge : edges)
    {
        if (edge.getFirst() >= points.size() || edge.getSecond() >= points.size())
            continue;

        graph[edge.getFirst()].push_back(edge.getSecond());
        graph[edge.getSecond()].push_back(edge.getFirst());
    }

    std::vector<Face> faces;
    std::set<Face> used;

    auto addFace = [&](const Face &face)
    {
        if (face.size() < 3 || face.size() > 4)
            return;

        if (!isPlanarFace(face, points))
            return;

        const Face canonical = canonicalFace(face);
        if (used.insert(canonical).second)
            faces.push_back(face);
    };

    Face path;

    auto dfs = [&](auto &&self, const std::size_t start, const std::size_t current) -> void
    {
        for (const auto next : graph[current])
        {
            if (next == start && path.size() >= 3)
            {
                addFace(path);
                continue;
            }

            if (path.size() == 4 ||
                std::find(path.begin(), path.end(), next) != path.end())
                continue;

            path.push_back(next);
            self(self, start, next);
            path.pop_back();
        }
    };

    for (std::size_t start = 0; start < points.size(); ++start)
    {
        path.clear();
        path.push_back(start);
        dfs(dfs, start, start);
    }

    return faces;
}

bool barycentricWeights(const Point &point,
                        const std::array<Point, 3> &triangle,
                        std::array<double, 3> &weights)
{
    const double x = point.getX();
    const double y = point.getY();

    const double x0 = triangle[0].getX();
    const double y0 = triangle[0].getY();
    const double x1 = triangle[1].getX();
    const double y1 = triangle[1].getY();
    const double x2 = triangle[2].getX();
    const double y2 = triangle[2].getY();

    const double denominator = (y1 - y2) * (x0 - x2) +
                               (x2 - x1) * (y0 - y2);

    if (std::abs(denominator) < EPS)
        return false;

    weights[0] = ((y1 - y2) * (x - x2) +
                  (x2 - x1) * (y - y2)) / denominator;
    weights[1] = ((y2 - y0) * (x - x2) +
                  (x0 - x2) * (y - y2)) / denominator;
    weights[2] = 1.0 - weights[0] - weights[1];

    return weights[0] >= -EPS && weights[1] >= -EPS && weights[2] >= -EPS &&
           weights[0] <= 1.0 + EPS && weights[1] <= 1.0 + EPS && weights[2] <= 1.0 + EPS;
}

bool faceDepthAtPoint(const Face &face,
                      const std::vector<Point> &points,
                      const BaseCamera &camera,
                      const Point &screenPoint,
                      double &depth)
{
    std::vector<Point> screenPoints;
    std::vector<double> depths;

    screenPoints.reserve(face.size());
    depths.reserve(face.size());

    for (const auto index : face)
    {
        const double currentDepth = cameraDepth(points[index], camera);

        if (currentDepth <= NEAR_PLANE)
            return false;

        const Point projection = camera.project(points[index]);

        if (!isFinitePoint(projection))
            return false;

        screenPoints.push_back(projection);
        depths.push_back(currentDepth);
    }

    const std::array<std::array<std::size_t, 3>, 2> triangleIndexes = {{
        {{0, 1, 2}},
        {{0, 2, 3}}
    }};

    const std::size_t trianglesCount = face.size() == 3 ? 1 : 2;

    for (std::size_t i = 0; i < trianglesCount; ++i)
    {
        const auto &indexes = triangleIndexes[i];
        const std::array<Point, 3> triangle = {{
            screenPoints[indexes[0]],
            screenPoints[indexes[1]],
            screenPoints[indexes[2]]
        }};

        std::array<double, 3> weights{};

        if (!barycentricWeights(screenPoint, triangle, weights))
            continue;

        const double invertedDepth = weights[0] / depths[indexes[0]] +
                                     weights[1] / depths[indexes[1]] +
                                     weights[2] / depths[indexes[2]];

        if (std::abs(invertedDepth) < EPS)
            return false;

        depth = 1.0 / invertedDepth;
        return true;
    }

    return false;
}

bool isPointHiddenByFaces(const Point &worldPoint,
                          const Point &screenPoint,
                          const Edge &edge,
                          const std::vector<Face> &faces,
                          const std::vector<Point> &points,
                          const BaseCamera &camera)
{
    const double pointDepth = cameraDepth(worldPoint, camera);

    for (const auto &face : faces)
    {
        if (faceHasEdge(face, edge))
            continue;

        double faceDepth = 0.0;

        if (!faceDepthAtPoint(face, points, camera, screenPoint, faceDepth))
            continue;

        if (faceDepth + DEPTH_EPS < pointDepth)
            return true;
    }

    return false;
}

bool isEdgeHiddenByFaces(const Edge &edge,
                         const std::vector<Face> &faces,
                         const std::vector<Point> &points,
                         const BaseCamera &camera)
{
    const Point &first = points[edge.getFirst()];
    const Point &second = points[edge.getSecond()];
    const std::array<double, 5> samples = {{0.1, 0.3, 0.5, 0.7, 0.9}};

    for (const double sample : samples)
    {
        const Point worldPoint = interpolate(first, second, sample);

        if (cameraDepth(worldPoint, camera) <= NEAR_PLANE)
            return false;

        const Point screenPoint = camera.project(worldPoint);

        if (!isFinitePoint(screenPoint))
            return false;

        if (!isPointHiddenByFaces(worldPoint, screenPoint, edge, faces, points, camera))
            return false;
    }

    return true;
}
}

void DrawerVisitor::visit(SkeletonModel &model)
{
    if (!_drawer || !_camera)
        return;

    const auto &points = model._modelStructure->getPoints();
    const auto &edges = model._modelStructure->getEdges();
    const auto faces = buildFaces(points, edges);

    for (const auto &edge : edges)
    {
        if (edge.getFirst() >= points.size() || edge.getSecond() >= points.size())
            continue;

        const auto &worldFirst = points[edge.getFirst()];
        const auto &worldSecond = points[edge.getSecond()];

        if (cameraDepth(worldFirst, *_camera) <= NEAR_PLANE ||
            cameraDepth(worldSecond, *_camera) <= NEAR_PLANE)
            continue;

        if (isEdgeHiddenByFaces(edge, faces, points, *_camera))
            continue;

        Point screenFirst = _camera->project(worldFirst);
        Point screenSecond = _camera->project(worldSecond);

        if (!isFinitePoint(screenFirst) || !isFinitePoint(screenSecond))
            continue;

        if (!clipLine(screenFirst, screenSecond))
            continue;

        _drawer->drawLine(screenFirst, screenSecond);
    }
}
