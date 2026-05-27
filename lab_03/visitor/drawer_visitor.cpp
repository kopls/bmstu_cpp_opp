#include "drawer_visitor.h"

#include "camera.h"
#include "z_buffer.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <set>
#include <vector>

namespace
{
constexpr double NEAR_PLANE = 1.0;
constexpr double EPS = 1e-9;
constexpr double DEPTH_EPS = 1e-2;

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

Point interpolate(const Point &first, const Point &second, double t)
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

bool isFinitePoint(const Point &point)
{
    return std::isfinite(point.getX()) &&
           std::isfinite(point.getY()) &&
           std::isfinite(point.getZ());
}

int intFloor(double value)
{
    return std::floor(value);
}

int intCeil(double value)
{
    return std::ceil(value);
}

bool projectPoint(const Point &point,
                  const BaseCamera &camera,
                  double width,
                  double height,
                  Point &projection,
                  double &depth)
{
    const Point relative = relativeToCamera(point, camera);

    const double cameraX = dot(relative, camera.getRight());
    const double cameraY = dot(relative, camera.getUp());
    depth = dot(relative, camera.getForward());

    if (depth <= NEAR_PLANE)
        return false;

    const double normalizedX = cameraX / depth;
    const double normalizedY = cameraY / depth;

    projection = Point((normalizedX + 1.0) * width / 2.0,
                       (1.0 - normalizedY) * height / 2.0,
                       0.0);

    return isFinitePoint(projection);
}

int outCode(double x, double y, double width, double height)
{
    int code = INSIDE;

    if (x < 0.0)
        code |= LEFT;
    else if (x > width)
        code |= RIGHT;

    if (y < 0.0)
        code |= TOP;
    else if (y > height)
        code |= BOTTOM;

    return code;
}

bool clipLine(Point &first, Point &second, double width, double height)
{
    double x1 = first.getX();
    double y1 = first.getY();
    double x2 = second.getX();
    double y2 = second.getY();

    int code1 = outCode(x1, y1, width, height);
    int code2 = outCode(x2, y2, width, height);

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

            x = x1 + (x2 - x1) * (height - y1) / (y2 - y1);
            y = height;
        }
        else if ((code & RIGHT) != 0)
        {
            if (std::abs(x2 - x1) < EPS)
                return false;

            y = y1 + (y2 - y1) * (width - x1) / (x2 - x1);
            x = width;
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
            code1 = outCode(x1, y1, width, height);
        }
        else
        {
            x2 = x;
            y2 = y;
            code2 = outCode(x2, y2, width, height);
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
        variants.push_back(direct);
        std::rotate(direct.begin(), direct.begin() + 1, direct.end());

        variants.push_back(reversed);
        std::rotate(reversed.begin(), reversed.begin() + 1, reversed.end());
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

bool isBoundaryFace(const Face &face, const std::vector<Point> &points)
{
    if (face.size() < 3)
        return false;

    const Point first = subtract(points[face[1]], points[face[0]]);
    const Point second = subtract(points[face[2]], points[face[0]]);
    const Point normal = cross(first, second);
    const double normalLength = length(normal);

    if (normalLength < EPS)
        return false;

    bool hasPositive = false;
    bool hasNegative = false;
    const double tolerance = normalLength * 1e-5;

    for (std::size_t i = 0; i < points.size(); ++i)
    {
        if (std::find(face.begin(), face.end(), i) != face.end())
            continue;

        const double side = dot(subtract(points[i], points[face[0]]), normal);

        if (side > tolerance)
            hasPositive = true;
        else if (side < -tolerance)
            hasNegative = true;

        if (hasPositive && hasNegative)
            return false;
    }

    return true;
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

        if (!isPlanarFace(face, points) || !isBoundaryFace(face, points))
            return;

        const Face canonical = canonicalFace(face);
        if (used.insert(canonical).second)
            faces.push_back(face);
    };

    Face path;

    auto dfs = [&](auto &&self, std::size_t start, std::size_t current) -> void
    {
        for (const auto next : graph[current])
        {
            if (next == start && path.size() >= 3)
            {
                addFace(path);
                continue;
            }

            if (path.size() == 4 || std::find(path.begin(), path.end(), next) != path.end())
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

void putTriangleToZBuffer(const std::array<Point, 3> &screen,
                          const std::array<double, 3> &depth,
                          ZBuffer &zBuffer)
{
    const double minX = std::min({screen[0].getX(), screen[1].getX(), screen[2].getX()});
    const double maxX = std::max({screen[0].getX(), screen[1].getX(), screen[2].getX()});
    const double minY = std::min({screen[0].getY(), screen[1].getY(), screen[2].getY()});
    const double maxY = std::max({screen[0].getY(), screen[1].getY(), screen[2].getY()});

    const int left = std::max(0, intFloor(minX));
    const int right = std::min(zBuffer.getWidth() - 1, intCeil(maxX));
    const int top = std::max(0, intFloor(minY));
    const int bottom = std::min(zBuffer.getHeight() - 1, intCeil(maxY));

    for (int y = top; y <= bottom; ++y)
    {
        for (int x = left; x <= right; ++x)
        {
            std::array<double, 3> weights{};
            const Point pixel(x + 0.5, y + 0.5, 0.0);

            if (!barycentricWeights(pixel, screen, weights))
                continue;

            const double invertedDepth = weights[0] / depth[0] +
                                         weights[1] / depth[1] +
                                         weights[2] / depth[2];

            if (std::abs(invertedDepth) < EPS)
                continue;

            zBuffer.putDepth(x, y, 1.0 / invertedDepth);
        }
    }
}

void putFaceToZBuffer(const Face &face,
                      const std::vector<Point> &points,
                      const BaseCamera &camera,
                      double width,
                      double height,
                      ZBuffer &zBuffer)
{
    std::vector<Point> screenPoints;
    std::vector<double> depths;

    screenPoints.reserve(face.size());
    depths.reserve(face.size());

    for (const auto index : face)
    {
        Point projection;
        double depth = 0.0;

        if (!projectPoint(points[index], camera, width, height, projection, depth))
            return;

        screenPoints.push_back(projection);
        depths.push_back(depth);
    }

    const std::array<std::array<std::size_t, 3>, 2> indexes = {{{{0, 1, 2}}, {{0, 2, 3}}}};
    const std::size_t trianglesCount = face.size() == 3 ? 1 : 2;

    for (std::size_t i = 0; i < trianglesCount; ++i)
    {
        const auto &triangleIndexes = indexes[i];

        const std::array<Point, 3> triangle = {{
            screenPoints[triangleIndexes[0]],
            screenPoints[triangleIndexes[1]],
            screenPoints[triangleIndexes[2]]
        }};

        const std::array<double, 3> triangleDepth = {{
            depths[triangleIndexes[0]],
            depths[triangleIndexes[1]],
            depths[triangleIndexes[2]]
        }};

        putTriangleToZBuffer(triangle, triangleDepth, zBuffer);
    }
}

void buildZBuffer(const std::vector<Point> &points,
                  const std::vector<Face> &faces,
                  const BaseCamera &camera,
                  double width,
                  double height,
                  ZBuffer &zBuffer)
{
    zBuffer.reset(width, height);

    for (const auto &face : faces)
        putFaceToZBuffer(face, points, camera, width, height, zBuffer);
}

bool isVisibleInZBuffer(const Point &worldPoint,
                        const BaseCamera &camera,
                        double width,
                        double height,
                        const ZBuffer &zBuffer,
                        Point &screenPoint)
{
    double depth = 0.0;

    if (!projectPoint(worldPoint, camera, width, height, screenPoint, depth))
        return false;

    if (screenPoint.getX() < 0.0 || screenPoint.getX() >= width ||
        screenPoint.getY() < 0.0 || screenPoint.getY() >= height)
        return false;

    const int x = intFloor(screenPoint.getX());
    const int y = intFloor(screenPoint.getY());

    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (zBuffer.isVisible(x + dx, y + dy, depth, DEPTH_EPS))
                return true;
        }
    }

    return false;
}

void drawVisibleEdge(const Edge &edge,
                     const std::vector<Point> &points,
                     const BaseCamera &camera,
                     BaseDrawer &drawer,
                     const ZBuffer &zBuffer)
{
    const Point &worldFirst = points[edge.getFirst()];
    const Point &worldSecond = points[edge.getSecond()];

    Point screenFirst;
    Point screenSecond;
    double firstDepth = 0.0;
    double secondDepth = 0.0;
    const double width = drawer.getWidth();
    const double height = drawer.getHeight();

    if (!projectPoint(worldFirst, camera, width, height, screenFirst, firstDepth) ||
        !projectPoint(worldSecond, camera, width, height, screenSecond, secondDepth))
        return;

    const double dx = screenSecond.getX() - screenFirst.getX();
    const double dy = screenSecond.getY() - screenFirst.getY();
    const int steps = std::max(1, intCeil(std::max(std::abs(dx), std::abs(dy))));

    bool segmentStarted = false;
    Point segmentStart;
    Point previousVisible;

    for (int i = 0; i <= steps; ++i)
    {
        const double t = static_cast<double>(i) / static_cast<double>(steps);
        Point currentScreen;
        const Point currentWorld = interpolate(worldFirst, worldSecond, t);
        const bool visible = isVisibleInZBuffer(currentWorld, camera, width, height, zBuffer, currentScreen);

        if (visible && !segmentStarted)
        {
            segmentStart = currentScreen;
            previousVisible = currentScreen;
            segmentStarted = true;
        }
        else if (visible)
        {
            previousVisible = currentScreen;
        }
        else if (segmentStarted)
        {
            Point clippedStart = segmentStart;
            Point clippedEnd = previousVisible;

            if (clipLine(clippedStart, clippedEnd, width, height))
                drawer.drawLine(clippedStart, clippedEnd);

            segmentStarted = false;
        }
    }

    if (segmentStarted)
    {
        Point clippedStart = segmentStart;
        Point clippedEnd = previousVisible;

        if (clipLine(clippedStart, clippedEnd, width, height))
            drawer.drawLine(clippedStart, clippedEnd);
    }
}
}

void DrawerVisitor::visit(SkeletonModel &model)
{
    if (!_drawer || !_camera)
        return;

    const auto &points = model._modelStructure->getPoints();
    const auto &edges = model._modelStructure->getEdges();
    const auto faces = buildFaces(points, edges);

    ZBuffer zBuffer(_drawer->getWidth(), _drawer->getHeight());
    buildZBuffer(points, faces, *_camera, _drawer->getWidth(), _drawer->getHeight(), zBuffer);

    for (const auto &edge : edges)
    {
        if (edge.getFirst() >= points.size() || edge.getSecond() >= points.size())
            continue;

        drawVisibleEdge(edge, points, *_camera, *_drawer, zBuffer);
    }
}
