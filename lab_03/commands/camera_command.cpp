#include "commands/camera_command.h"

AddCamera::AddCamera(std::shared_ptr<Object> camera, ID id)
    : method(&SolutionScene::addObjectWithId), camera(camera), id(id)
{
}

void AddCamera::execute()
{
    ((*(proxy.scene)).*method)(camera, id);
}

DeleteCamera::DeleteCamera(std::size_t id)
    : method(&SolutionScene::deleteObject), id(id)
{
}

void DeleteCamera::execute()
{
    ((*(proxy.scene)).*method)(id);
}

MoveCamera::MoveCamera(std::size_t id, double dx, double dy, double dz)
    : method(&SolutionTransform::moveSceneObject), id(id), dx(dx), dy(dy), dz(dz)
{
}

void MoveCamera::execute()
{
    ((*(proxy.transform)).*method)(currentScene(), id, dx, dy, dz);
}

RotateCamera::RotateCamera(std::size_t id, double ox, double oy, double oz)
    : method(&SolutionTransform::rotateSceneObject), id(id), ox(ox), oy(oy), oz(oz)
{
}

void RotateCamera::execute()
{
    ((*(proxy.transform)).*method)(currentScene(), id, ox, oy, oz);
}

SetCamera::SetCamera(std::size_t id)
    : method(&SolutionScene::setCamera), id(id)
{
}

void SetCamera::execute()
{
    ((*(proxy.scene)).*method)(id);
}

GetCamera::GetCamera(std::shared_ptr<BaseCamera> &camera)
    : method(&SolutionScene::getCamera), camera(camera)
{
}

void GetCamera::execute()
{
    camera = ((*(proxy.scene)).*method)();
}
