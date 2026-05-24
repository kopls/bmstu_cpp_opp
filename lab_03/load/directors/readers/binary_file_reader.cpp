#include "binary_file_reader.h"

#include <array>
#include <cstring>
#include <stdexcept>

BinaryFileReader::BinaryFileReader()
    : _file(std::make_shared<std::ifstream>())
{
}

BinaryFileReader::BinaryFileReader(std::shared_ptr<std::ifstream> file)
    : _file(file)
{
}

void BinaryFileReader::open(const std::string &fileName)
{
    if (!_file)
        _file = std::make_shared<std::ifstream>();

    _file->open(fileName, std::ios::binary);

    if (!_file->is_open())
        throw std::runtime_error("BinaryFileReader: cannot open file");
}

void BinaryFileReader::close()
{
    if (_file && _file->is_open())
        _file->close();
}

void BinaryFileReader::checkStream() const
{
    if (!_file || !_file->good())
        throw std::runtime_error("BinaryFileReader: read error");
}

template <typename T>
T BinaryFileReader::readValue()
{
    std::array<char, sizeof(T)> buffer{};
    _file->read(buffer.data(), sizeof(T));
    checkStream();

    T value{};
    std::memcpy(&value, buffer.data(), sizeof(T));
    return value;
}

std::size_t BinaryFileReader::readCount()
{
    return readValue<std::size_t>();
}

Point BinaryFileReader::readPoint()
{
    const double x = readValue<double>();
    const double y = readValue<double>();
    const double z = readValue<double>();

    return Point(x, y, z);
}

std::vector<Point> BinaryFileReader::readPoints()
{
    const std::size_t count = readCount();

    if (count == 0)
        throw std::runtime_error("BinaryFileReader: point count is zero");

    std::vector<Point> points;
    points.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
        points.push_back(readPoint());

    return points;
}

std::vector<Edge> BinaryFileReader::readEdges(std::size_t pointCount)
{
    const std::size_t count = readCount();

    if (count == 0)
        throw std::runtime_error("BinaryFileReader: edge count is zero");

    std::vector<Edge> edges;
    edges.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        const std::size_t first = readValue<std::size_t>();
        const std::size_t second = readValue<std::size_t>();

        if (first >= pointCount || second >= pointCount)
            throw std::runtime_error("BinaryFileReader: edge index is out of range");

        edges.emplace_back(first, second);
    }

    return edges;
}
