#include "model_command.h"

#include <stdexcept>

namespace
{
std::shared_ptr<Object> getObjectOrThrow(std::shared_ptr<Scene> scene, std::size_t id, const char *message)
{
    auto iter = scene->getObject(id);

    if (iter == scene->end())
        throw std::logic_error(message);

    return *iter;
}

Iterator getIteratorOrThrow(std::shared_ptr<Scene> scene, std::size_t id, const char *message)
{
    auto iter = scene->getObject(id);

    if (iter == scene->end())
        throw std::logic_error(message);

    return iter;
}
}

MoveModel::MoveModel(std::size_t id, double dx, double dy, double dz)
    : method(&TransformManager::moveObject), id(id), dx(dx), dy(dy), dz(dz)
{
}

void MoveModel::execute()
{
    if (!proxy.transform)
        throw std::logic_error("MoveModel: transform manager is not set");

    auto object = getObjectOrThrow(currentScene(), id, "MoveModel: model not found");
    ((*(proxy.transform)).*method)(object, dx, dy, dz);
}

ScaleModel::ScaleModel(std::size_t id, double kx, double ky, double kz)
    : method(&TransformManager::scaleObject), id(id), kx(kx), ky(ky), kz(kz)
{
}

void ScaleModel::execute()
{
    if (!proxy.transform)
        throw std::logic_error("ScaleModel: transform manager is not set");

    auto object = getObjectOrThrow(currentScene(), id, "ScaleModel: model not found");
    ((*(proxy.transform)).*method)(object, kx, ky, kz);
}

RotateModel::RotateModel(std::size_t id, double ox, double oy, double oz)
    : method(&TransformManager::rotateObject), id(id), ox(ox), oy(oy), oz(oz)
{
}

void RotateModel::execute()
{
    if (!proxy.transform)
        throw std::logic_error("RotateModel: transform manager is not set");

    auto object = getObjectOrThrow(currentScene(), id, "RotateModel: model not found");
    ((*(proxy.transform)).*method)(object, ox, oy, oz);
}

TransformModel::TransformModel(std::size_t id, const Point &move, const Point &scale, const Point &rotate)
    : method(&TransformManager::transformObject), id(id), move(move), scale(scale), rotate(rotate)
{
}

void TransformModel::execute()
{
    if (!proxy.transform)
        throw std::logic_error("TransformModel: transform manager is not set");

    auto object = getObjectOrThrow(currentScene(), id, "TransformModel: model not found");
    ((*(proxy.transform)).*method)(object, move, scale, rotate);
}

DeleteModel::DeleteModel(std::size_t id)
    : method(&Scene::deleteObject), id(id)
{
}

void DeleteModel::execute()
{
    auto scene = currentScene();
    auto iter = getIteratorOrThrow(scene, id, "DeleteModel: model not found");
    ((*scene).*method)(iter);
}
