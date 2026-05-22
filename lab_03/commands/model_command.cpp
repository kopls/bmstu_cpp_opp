#include "model_command.h"

MoveModel::MoveModel(std::size_t id, double dx, double dy, double dz)
    : method(static_cast<Action>(&TransformManager::moveObject)), id(id), dx(dx), dy(dy), dz(dz)
{
}

void MoveModel::execute()
{
    ((*(proxy.transform)).*method)(currentScene(), id, dx, dy, dz);
}

ScaleModel::ScaleModel(std::size_t id, double kx, double ky, double kz)
    : method(static_cast<Action>(&TransformManager::scaleObject)), id(id), kx(kx), ky(ky), kz(kz)
{
}

void ScaleModel::execute()
{
    ((*(proxy.transform)).*method)(currentScene(), id, kx, ky, kz);
}

RotateModel::RotateModel(std::size_t id, double ox, double oy, double oz)
    : method(static_cast<Action>(&TransformManager::rotateObject)), id(id), ox(ox), oy(oy), oz(oz)
{
}

void RotateModel::execute()
{
    ((*(proxy.transform)).*method)(currentScene(), id, ox, oy, oz);
}

TransformModel::TransformModel(std::size_t id, const Point &move, const Point &scale, const Point &rotate)
    : method(static_cast<Action>(&TransformManager::transformObject)), id(id), move(move), scale(scale), rotate(rotate)
{
}

void TransformModel::execute()
{
    ((*(proxy.transform)).*method)(currentScene(), id, move, scale, rotate);
}

DeleteModel::DeleteModel(std::size_t id)
    : method(&Scene::deleteObject), id(id)
{
}

void DeleteModel::execute()
{
    ((*currentScene()).*method)(id);
}
