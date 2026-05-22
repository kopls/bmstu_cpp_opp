#include "scene.h"

#include <stdexcept>

void Scene::addObject(const std::shared_ptr<Object> &object)
{
    if (!object)
        throw std::logic_error("Scene: object is not set");

    _objects.push_back(object);
}

void Scene::addObject(const std::shared_ptr<Object> &object, const std::shared_ptr<std::size_t> &id)
{
    addObject(object);

    if (id)
        *id = object->getId();
}

void Scene::deleteObject(Iterator &iter)
{
    _objects.erase(iter);
}

void Scene::deleteObject(std::size_t id)
{
    auto iter = getObject(id);

    if (iter == end())
        throw std::logic_error("Scene: object not found");

    deleteObject(iter);
}

Iterator Scene::getObject(const std::size_t id)
{
    auto iter = begin();

    for (; iter != end() && (*iter)->getId() != id; ++iter);

    return iter;
}

Iterator Scene::begin()
{
    return _objects.begin();
}

Iterator Scene::end()
{
    return _objects.end();
}
