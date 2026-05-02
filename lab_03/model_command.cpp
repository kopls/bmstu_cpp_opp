#include "model_command.h"

MoveModel::MoveModel(const double dx, const double dy, const double dz, const std::size_t id) : _dx(dx), _dy(dy), _dz(dz), _id(id) {}

void MoveModel::execute()
{
    auto iter = _sceneManager->getScene()->getObject(_id);
    auto model = *iter;
    _transformManager->moveObject(model, _dx, _dy, _dz);
}

ScaleModel::ScaleModel(const double kx, const double ky, const double kz, const std::size_t id) : _kx(kx), _ky(ky), _kz(kz), _id(id) {}

void ScaleModel::execute()
{
    auto iter = _sceneManager->getScene()->getObject(_id);
    auto model = *iter;
    _transformManager->scaleObject(model, _kx, _ky, _kz);
}

RotateModel::RotateModel(const double ox, const double oy, const double oz, const std::size_t id) : _ox(ox), _oy(oy), _oz(oz), _id(id) {}

void ScaleModel::execute()
{
    auto iter = _sceneManager->getScene()->getObject(_id);
    auto model = *iter;
    _transformManager->rotateObject(model, _ox, _oy, _oz);
}

TransformModel::TransformModel(const Point &move, const Point &scale, const Point &rotate, const std::size_t id) : _move(move), _scale(scale), _rotate(rotate), _id(id) {}

void TransformModel::execute()
{
    auto iter = _sceneManager->getScene()->getObject(_id);
    auto model = *iter;
    _transformManager->transformObject(model, _move, _scale, _rotate);
}

DeleteModel::DeleteModel(std::size_t id) : _id(id) {}

void DeleteModel::execute()
{
    auto iter = _sceneManager->getScene()->getObject(_id);
    auto model = *iter;
    _scene->deleteObject(model);
}

