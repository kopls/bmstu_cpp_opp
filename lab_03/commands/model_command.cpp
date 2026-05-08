#include "commands/model_command.h"

#include <stdexcept>

namespace
{
std::shared_ptr<Object> getObjectById(const std::shared_ptr<SceneManager> &sceneManager, std::size_t id)
{
    if (!sceneManager || !sceneManager->getScene())
        throw std::logic_error("ModelCommand: scene is not set");

    auto scene = sceneManager->getScene();
    auto iter = scene->getObject(id);

    if (iter == scene->end())
        throw std::logic_error("ModelCommand: object not found");

    return *iter;
}
}

MoveModel::MoveModel(std::shared_ptr<SceneManager> sceneManager,
                     std::shared_ptr<TransformManager> transformManager,
                     std::size_t id,
                     double dx,
                     double dy,
                     double dz,
                     Action action)
    : _sceneManager(sceneManager),
      _receiver(transformManager),
      _action(action),
      _id(id),
      _dx(dx),
      _dy(dy),
      _dz(dz)
{
}

void MoveModel::execute()
{
    auto object = getObjectById(_sceneManager, _id);
    ((*_receiver).*_action)(object, _dx, _dy, _dz);
}

ScaleModel::ScaleModel(std::shared_ptr<SceneManager> sceneManager,
                       std::shared_ptr<TransformManager> transformManager,
                       std::size_t id,
                       double kx,
                       double ky,
                       double kz,
                       Action action)
    : _sceneManager(sceneManager),
      _receiver(transformManager),
      _action(action),
      _id(id),
      _kx(kx),
      _ky(ky),
      _kz(kz)
{
}

void ScaleModel::execute()
{
    auto object = getObjectById(_sceneManager, _id);
    ((*_receiver).*_action)(object, _kx, _ky, _kz);
}

RotateModel::RotateModel(std::shared_ptr<SceneManager> sceneManager,
                         std::shared_ptr<TransformManager> transformManager,
                         std::size_t id,
                         double ox,
                         double oy,
                         double oz,
                         Action action)
    : _sceneManager(sceneManager),
      _receiver(transformManager),
      _action(action),
      _id(id),
      _ox(ox),
      _oy(oy),
      _oz(oz)
{
}

void RotateModel::execute()
{
    auto object = getObjectById(_sceneManager, _id);
    ((*_receiver).*_action)(object, _ox, _oy, _oz);
}

TransformModel::TransformModel(std::shared_ptr<SceneManager> sceneManager,
                               std::shared_ptr<TransformManager> transformManager,
                               std::size_t id,
                               const Point &move,
                               const Point &scale,
                               const Point &rotate,
                               Action action)
    : _sceneManager(sceneManager),
      _receiver(transformManager),
      _action(action),
      _id(id),
      _move(move),
      _scale(scale),
      _rotate(rotate)
{
}

void TransformModel::execute()
{
    auto object = getObjectById(_sceneManager, _id);
    ((*_receiver).*_action)(object, _move, _scale, _rotate);
}

DeleteModel::DeleteModel(std::shared_ptr<SceneManager> sceneManager,
                         std::size_t id,
                         Action action)
    : _sceneManager(sceneManager),
      _action(action),
      _id(id)
{
}

void DeleteModel::execute()
{
    if (!_sceneManager || !_sceneManager->getScene())
        throw std::logic_error("DeleteModel: scene is not set");

    auto scene = _sceneManager->getScene();
    auto iter = scene->getObject(_id);

    if (iter == scene->end())
        throw std::logic_error("DeleteModel: object not found");

    ((*scene).*_action)(iter);
}
