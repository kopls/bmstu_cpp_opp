#ifndef EDGE_H
#define EDGE_H

#include <cstddef>

class Edge
{
public:
    Edge() = default;
    ~Edge() = default;
    Edge(const std::size_t firstIndex, const std::size_t secondIndex);
    Edge(const Edge &edge) = default;

    void setFirst(const std::size_t index);
    void setSecond(const std::size_t index);

    std::size_t getFirst() const;
    std::size_t getSecond() const;

private:
    std::size_t _first;
    std::size_t _second;
};

#endif
