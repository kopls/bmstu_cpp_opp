#include "scene_builder.h"

#include <stdexcept>

void SceneBuilder::build()
{
    _scene = std::make_shared<Scene>();
}

void SceneBuilder::buildObject(const std::shared_ptr<Object> &object)
{
    if (!isBuild())
        throw std::logic_error("SceneBuilder: scene is not built");

    _scene->addObject(object);
}

bool SceneBuilder::isBuild() const
{
    return _scene != nullptr;
}

std::shared_ptr<Scene> SceneBuilder::get()
{
    if (!isBuild())
        throw std::logic_error("SceneBuilder: scene is not built");

    return _scene;
}
