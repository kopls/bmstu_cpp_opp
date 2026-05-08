#include "commands/camera_command.h"

#include <stdexcept>

namespace
{
Iterator getIteratorOrThrow(std::shared_ptr<Scene> scene, std::size_t id, const char *message)
{
    auto iter = scene->getObject(id);

    if (iter == scene->end())
        throw std::logic_error(message);

    return iter;
}
}

AddCamera::AddCamera(std::shared_ptr<Object> camera, ID id)
    : method(&Scene::addObject), camera(camera), id(id)
{
}

void AddCamera::execute()
{
    if (!camera)
        throw std::logic_error("AddCamera: camera is not set");

    auto scene = currentScene();
    ((*scene).*method)(camera);

    if (id)
        *id = camera->getId();
}

DeleteCamera::DeleteCamera(std::size_t id)
    : method(&Scene::deleteObject), id(id)
{
}

void DeleteCamera::execute()
{
    auto scene = currentScene();
    auto iter = getIteratorOrThrow(scene, id, "DeleteCamera: camera not found");
    ((*scene).*method)(iter);
}

MoveCamera::MoveCamera(std::size_t id, double dx, double dy, double dz)
    : method(&TransformManager::moveObject), id(id), dx(dx), dy(dy), dz(dz)
{
}

void MoveCamera::execute()
{
    if (!proxy.transform)
        throw std::logic_error("MoveCamera: transform manager is not set");

    auto scene = currentScene();
    auto iter = getIteratorOrThrow(scene, id, "MoveCamera: camera not found");
    std::shared_ptr<Object> object = *iter;

    ((*(proxy.transform)).*method)(object, dx, dy, dz);
}

SetCamera::SetCamera(std::size_t id)
    : method(&SceneManager::setCamera), id(id)
{
}

void SetCamera::execute()
{
    if (!proxy.scene)
        throw std::logic_error("SetCamera: scene manager is not set");

    ((*(proxy.scene)).*method)(id);
}

GetCamera::GetCamera(std::shared_ptr<BaseCamera> &camera)
    : method(&SceneManager::getCamera), camera(camera)
{
}

void GetCamera::execute()
{
    if (!proxy.scene)
        throw std::logic_error("GetCamera: scene manager is not set");

    camera = ((*(proxy.scene)).*method)();
}
