#ifndef BASE_READER_H
#define BASE_READER_H

#include <cstddef>
#include <string>
#include <vector>

#include "point.h"
#include "edge.h"

class BaseReader
{
public:
    BaseReader() = default;
    virtual ~BaseReader() = default;

    virtual void open(const std::string &fileName) = 0;
    virtual void close() = 0;

    virtual std::size_t readCount() = 0;
    virtual Point readPoint() = 0;
    virtual std::vector<Point> readPoints() = 0;
    virtual std::vector<Edge> readEdges(std::size_t pointCount) = 0;
};

#endif
