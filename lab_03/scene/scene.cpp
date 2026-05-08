#include "scene.h"

void Scene::addObject(const std::shared_ptr<Object> &object)
{
    _objects.push_back(object);
}

void Scene::deleteObject(Iterator &iter)
{
    _objects.erase(iter);
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
