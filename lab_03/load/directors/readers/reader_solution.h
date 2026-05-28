#ifndef READER_SOLUTION_H
#define READER_SOLUTION_H

#include <functional>
#include <map>
#include <memory>

#include "base_reader.h"
#include "model_load_options.h"

class ReaderSolution
{
public:
    ReaderSolution();

    std::shared_ptr<BaseReader> resolve(ModelFileFormat format) const;

private:
    using Creator = std::function<std::shared_ptr<BaseReader>()>;

    std::map<ModelFileFormat, Creator> _creators;
};

#endif
