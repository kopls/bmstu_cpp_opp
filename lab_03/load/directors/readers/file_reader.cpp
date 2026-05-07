#include "file_reader.h"

#include <stdexcept>

FileReader::FileReader()
    : _file(std::make_shared<std::ifstream>())
{
}

FileReader::FileReader(std::shared_ptr<std::ifstream> file)
    : _file(file)
{
}

void FileReader::open(const std::string &fileName)
{
    if (!_file)
        _file = std::make_shared<std::ifstream>();

    _file->open(fileName);

    if (!_file->is_open())
        throw std::runtime_error("FileReader: cannot open file");
}

void FileReader::close()
{
    if (_file && _file->is_open())
        _file->close();
}

void FileReader::checkStream() const
{
    if (!_file || !_file->good())
        throw std::runtime_error("FileReader: read error");
}

std::size_t FileReader::readCount()
{
    std::size_t count = 0;
    (*_file) >> count;
    checkStream();

    return count;
}

Point FileReader::readPoint()
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    (*_file) >> x >> y >> z;
    checkStream();

    return Point(x, y, z);
}

std::vector<Point> FileReader::readPoints()
{
    const std::size_t count = readCount();

    if (count == 0)
        throw std::runtime_error("FileReader: point count is zero");

    std::vector<Point> points;
    points.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
        points.push_back(readPoint());

    return points;
}

std::vector<Edge> FileReader::readEdges(std::size_t pointCount)
{
    const std::size_t count = readCount();

    if (count == 0)
        throw std::runtime_error("FileReader: edge count is zero");

    std::vector<Edge> edges;
    edges.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        std::size_t first = 0;
        std::size_t second = 0;

        (*_file) >> first >> second;
        checkStream();

        if (first >= pointCount || second >= pointCount)
            throw std::runtime_error("FileReader: edge index is out of range");

        edges.emplace_back(first, second);
    }

    return edges;
}
