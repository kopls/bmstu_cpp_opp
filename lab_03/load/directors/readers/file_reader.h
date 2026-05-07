#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <memory>

#include "base_reader.h"

class FileReader : public BaseReader
{
public:
    FileReader();
    explicit FileReader(std::shared_ptr<std::ifstream> file);
    ~FileReader() override = default;

    void open(const std::string &fileName) override;
    void close() override;

    std::size_t readCount() override;
    Point readPoint() override;
    std::vector<Point> readPoints() override;
    std::vector<Edge> readEdges(std::size_t pointCount) override;

private:
    void checkStream() const;

    std::shared_ptr<std::ifstream> _file;
};

#endif
