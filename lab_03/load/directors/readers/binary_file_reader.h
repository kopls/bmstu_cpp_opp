#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H

#include <fstream>
#include <memory>

#include "base_reader.h"

class BinaryFileReader : public BaseReader
{
public:
    BinaryFileReader();
    explicit BinaryFileReader(std::shared_ptr<std::ifstream> file);
    ~BinaryFileReader() override = default;

    void open(const std::string &fileName) override;
    void close() override;

    std::size_t readCount() override;
    Point readPoint() override;
    std::vector<Point> readPoints() override;
    std::vector<Edge> readEdges(std::size_t pointCount) override;

private:
    template <typename T>
    T readValue();

    void checkStream() const;

    std::shared_ptr<std::ifstream> _file;
};

#endif
