#ifndef BASE_MODEL_BUILD_DIRECTOR_H
#define BASE_MODEL_BUILD_DIRECTOR_H

#include <memory>
#include <string>

#include "base_director.h"
#include "base_model_builder.h"
#include "object.h"

class BaseModelBuildDirector : public BaseDirector
{
public:
    BaseModelBuildDirector() = default;
    ~BaseModelBuildDirector() override = default;

    virtual std::shared_ptr<Object> load(const std::string &fileName) = 0;
    virtual std::shared_ptr<Object> loadFromCurrentSource() = 0;
};

#endif
