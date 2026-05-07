#ifndef FILE_MODEL_BUILD_DIRECTOR_H
#define FILE_MODEL_BUILD_DIRECTOR_H

#include <memory>

#include "base_model_build_director.h"
#include "base_reader.h"
#include "file_reader.h"
#include "model_builder.h"

class FileModelBuildDirector : public BaseModelBuildDirector
{
public:
    FileModelBuildDirector();
    FileModelBuildDirector(std::shared_ptr<BaseReader> reader,
                           std::shared_ptr<BaseModelBuilder> builder);
    ~FileModelBuildDirector() override = default;

    std::shared_ptr<Object> load(const std::string &fileName) override;
    std::shared_ptr<Object> loadFromCurrentSource() override;

private:
    std::shared_ptr<BaseReader> _reader;
    std::shared_ptr<BaseModelBuilder> _builder;
};

#endif
