#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include <memory>

#include "base_scene_builder.h"

class SceneBuilder : public BaseSceneBuilder
{
public:
    SceneBuilder() = default;
    ~SceneBuilder() override = default;

    void build() override;
    void buildObject(const std::shared_ptr<Object> &object) override;
    bool isBuild() const override;

    std::shared_ptr<Scene> get() override;

private:
    std::shared_ptr<Scene> _scene;
};

#endif
