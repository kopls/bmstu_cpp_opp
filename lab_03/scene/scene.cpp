#include "scene.h"

#include <stdexcept>

#include "composite.h"

std::shared_ptr<Scene> Scene::clone() const
{
    auto scene = std::make_shared<Scene>();

    for (const auto &object : _objects)
        scene->addObject(object->clone());

    return scene;
}

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

void Scene::addObjectWithId(const std::shared_ptr<Object> &object, const std::shared_ptr<std::size_t> &id)
{
    addObject(object, id);
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

std::shared_ptr<BaseCamera> Scene::getCamera(std::size_t id)
{
    for (auto &object : _objects)
    {
        auto camera = getCamera(object, id);
        if (camera)
            return camera;
    }

    return nullptr;
}

std::shared_ptr<BaseCamera> Scene::getCamera(const std::shared_ptr<Object> &object, std::size_t id)
{
    if (!object)
        return nullptr;

    if (object->getId() == id && object->isCamera())
        return std::shared_ptr<BaseCamera>(object, object->cameraPtr());

    if (object->isComposite())
    {
        for (auto iter = object->begin(); iter != object->end(); ++iter)
        {
            auto camera = getCamera(*iter, id);
            if (camera)
                return camera;
        }
    }

    return nullptr;
}

std::vector<std::size_t> Scene::getCameraIds() const
{
    std::vector<std::size_t> ids;

    for (const auto &object : _objects)
        collectCameraIds(object, ids);

    return ids;
}

void Scene::collectCameraIds(const std::shared_ptr<Object> &object, std::vector<std::size_t> &ids) const
{
    if (!object)
        return;

    if (object->isCamera())
        ids.push_back(object->getId());

    if (object->isComposite())
    {
        for (auto iter = object->begin(); iter != object->end(); ++iter)
            collectCameraIds(*iter, ids);
    }
}

std::size_t Scene::visibleObjectCount() const
{
    std::size_t count = 0;

    for (const auto &object : _objects)
        if (object && object->isVisible())
            ++count;

    return count;
}

void Scene::collectVisibleObjectsToComposite()
{
    std::vector<std::shared_ptr<Object>> visibleObjects;
    std::vector<std::shared_ptr<Object>> otherObjects;

    for (const auto &object : _objects)
    {
        if (object && object->isVisible())
            visibleObjects.push_back(object);
        else
            otherObjects.push_back(object);
    }

    if (visibleObjects.empty())
        return;

    otherObjects.push_back(std::make_shared<Composite>(visibleObjects));
    _objects = otherObjects;
}

void Scene::splitCompositesToObjects()
{
    std::vector<std::shared_ptr<Object>> objects;

    for (const auto &object : _objects)
    {
        if (object && object->isComposite())
        {
            const auto elements = object->getElements();
            for (const auto &element : elements)
                objects.push_back(element);
        }
        else
            objects.push_back(object);
    }

    _objects = objects;
}

Iterator Scene::begin()
{
    return _objects.begin();
}

Iterator Scene::end()
{
    return _objects.end();
}
