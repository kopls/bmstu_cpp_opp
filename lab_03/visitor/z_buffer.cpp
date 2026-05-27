#include "z_buffer.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace
{
int intCeil(double value)
{
    return std::ceil(value);
}
}

ZBuffer::ZBuffer(double width, double height)
{
    reset(width, height);
}

void ZBuffer::reset(double width, double height)
{
    _width = std::max(1, intCeil(width));
    _height = std::max(1, intCeil(height));
    _depths.assign(_width * _height, std::numeric_limits<double>::infinity());
}

void ZBuffer::clear()
{
    std::fill(_depths.begin(), _depths.end(), std::numeric_limits<double>::infinity());
}

int ZBuffer::getWidth() const
{
    return _width;
}

int ZBuffer::getHeight() const
{
    return _height;
}

bool ZBuffer::contains(int x, int y) const
{
    return x >= 0 && y >= 0 && x < _width && y < _height;
}

void ZBuffer::putDepth(int x, int y, double depth)
{
    if (!contains(x, y))
        return;

    auto &current = _depths[index(x, y)];
    if (depth < current)
        current = depth;
}

bool ZBuffer::isVisible(int x, int y, double depth, double eps) const
{
    if (!contains(x, y))
        return false;

    return depth <= _depths[index(x, y)] + eps;
}

int ZBuffer::index(int x, int y) const
{
    return y * _width + x;
}
