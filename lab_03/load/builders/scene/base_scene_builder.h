#ifndef BASE_SCENE_BUILDER_H
#define BASE_SCENE_BUILDER_H

#include <memory>

#include "base_builder.h"
#include "scene.h"
#include "object.h"

class BaseSceneBuilder : public BaseBuilder
{
public:
    BaseSceneBuilder() = default;
    ~BaseSceneBuilder() override = default;

    virtual void buildObject(const std::shared_ptr<Object> &object) = 0;

    virtual std::shared_ptr<Scene> get() = 0;
};

#endif
