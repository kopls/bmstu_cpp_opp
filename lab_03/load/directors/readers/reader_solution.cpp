#include "reader_solution.h"

#include <stdexcept>

#include "binary_file_reader.h"
#include "file_reader.h"

ReaderSolution::ReaderSolution()
{
    _creators[ModelFileFormat::Text] = []()
    {
        return std::make_shared<FileReader>();
    };

    _creators[ModelFileFormat::Binary] = []()
    {
        return std::make_shared<BinaryFileReader>();
    };
}

std::shared_ptr<BaseReader> ReaderSolution::resolve(ModelFileFormat format) const
{
    const auto iterator = _creators.find(format);

    if (iterator == _creators.end())
        throw std::logic_error("ReaderSolution: unsupported file format");

    return iterator->second();
}
