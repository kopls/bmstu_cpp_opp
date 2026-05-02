#include "camera_command.h"

AddCamera::AddCamera(const ID &id, const double x, const double y, const double z) : _x(x), _y(y), _z(z), _id(id) {}

void AddCamera::execute()
{
    Point location(_x, _y, _z);

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(location);

    _sceneManager->getScene()->addObject(camera);

    (*_id) = camera->getId();
};


DeleteCamera::DeleteCamera(const std::size_t id) : _id(id) {}

void DeleteCamera::execute()
{
    auto iter = _sceneManager->getScene()->getObject(_id);
    _sceneManager->getScene()->deleteObject(iter);
}


MoveCamera::MoveCamera(const double dx, const double dy, const double dz, const std::size_t id) :
    _dx(dx), _dy(dy), _dz(dz), _id(id) {}

void MoveCamera::execute()
{
    auto iter = _sceneManager->getScene()->getObject(_id);
    auto model = *iter;
    _transformManager->moveObject(model, _dx, _dy, _dz);
}


SetCamera::SetCamera(const std::size_t id) : _id(id) {}

void SetCamera::execute()
{
    _sceneManager->setCamera(_id);
}
