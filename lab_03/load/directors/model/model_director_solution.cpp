#include "model_director_solution.h"

#include <stdexcept>

#include "file_model_build_director.h"

ModelDirectorSolution::ModelDirectorSolution()
{
    _creators[ModelFileFormat::Text] = [](std::shared_ptr<BaseReader> reader,
                                          std::shared_ptr<BaseModelBuilder> builder)
    {
        return std::make_shared<FileModelBuildDirector>(reader, builder);
    };

    _creators[ModelFileFormat::Binary] = [](std::shared_ptr<BaseReader> reader,
                                            std::shared_ptr<BaseModelBuilder> builder)
    {
        return std::make_shared<FileModelBuildDirector>(reader, builder);
    };
}

std::shared_ptr<BaseModelBuildDirector> ModelDirectorSolution::resolve(ModelFileFormat format,
                                                                       std::shared_ptr<BaseReader> reader,
                                                                       std::shared_ptr<BaseModelBuilder> builder) const
{
    const auto iterator = _creators.find(format);

    if (iterator == _creators.end())
        throw std::logic_error("ModelDirectorSolution: unsupported file format");

    return iterator->second(reader, builder);
}
