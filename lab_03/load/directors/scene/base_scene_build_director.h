#ifndef BASE_SCENE_BUILD_DIRECTOR_H
#define BASE_SCENE_BUILD_DIRECTOR_H

#include <memory>
#include <string>

#include "base_director.h"
#include "base_scene_builder.h"
#include "scene.h"

class BaseSceneBuildDirector : public BaseDirector
{
public:
    BaseSceneBuildDirector() = default;
    ~BaseSceneBuildDirector() override = default;

    virtual std::shared_ptr<Scene> load(const std::string &fileName) = 0;
};

#endif
