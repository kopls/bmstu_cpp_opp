#ifndef MODEL_LOAD_MODERATOR_H
#define MODEL_LOAD_MODERATOR_H

#include <memory>

#include "base_load_moderator.h"
#include "base_model_build_director.h"

class ModelLoadModerator : public BaseLoadModerator
{
public:
    ModelLoadModerator() = default;
    ~ModelLoadModerator() override = default;
    explicit ModelLoadModerator(std::shared_ptr<BaseModelBuildDirector> director);

    std::shared_ptr<Object> load(const std::string &fileName) override;

    void setDirector(std::shared_ptr<BaseModelBuildDirector> director);

private:
    std::shared_ptr<BaseModelBuildDirector> _director;
};

#endif
