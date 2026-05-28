#ifndef MODEL_DIRECTOR_SOLUTION_H
#define MODEL_DIRECTOR_SOLUTION_H

#include <functional>
#include <map>
#include <memory>

#include "base_model_build_director.h"
#include "base_model_builder.h"
#include "base_reader.h"
#include "model_load_options.h"

class ModelDirectorSolution
{
public:
    ModelDirectorSolution();

    std::shared_ptr<BaseModelBuildDirector> resolve(ModelFileFormat format,
                                                    std::shared_ptr<BaseReader> reader,
                                                    std::shared_ptr<BaseModelBuilder> builder) const;

private:
    using Creator = std::function<std::shared_ptr<BaseModelBuildDirector>(std::shared_ptr<BaseReader>,
                                                                          std::shared_ptr<BaseModelBuilder>)>;

    std::map<ModelFileFormat, Creator> _creators;
};

#endif
