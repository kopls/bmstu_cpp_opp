#include "edge.h"

Edge::Edge(const std::size_t firstIndex, const std::size_t secondIndex)
{
    setFirst(firstIndex);
    setSecond(secondIndex);
}

std::size_t Edge::getFirst() const
{
    return _first;
}

std::size_t Edge::getSecond() const
{
    return _second;
}

void Edge::setFirst(const std::size_t index)
{
    _first = index;
}

void Edge::setSecond(const std::size_t index)
{
    _second = index;
}

