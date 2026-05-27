#include "solution_draw.h"

#include <stdexcept>

SolutionDraw::SolutionDraw(std::shared_ptr<DrawManager> manager,
                           std::shared_ptr<BaseVisitor> visitor,
                           std::shared_ptr<BaseDrawer> drawer)
    : _manager(manager), _visitor(visitor), _drawer(drawer)
{
}

void SolutionDraw::setDrawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}

void SolutionDraw::setVisitor(std::shared_ptr<BaseVisitor> visitor)
{
    _visitor = visitor;
}

void SolutionDraw::drawSceneWithCamera(std::shared_ptr<Scene> scene, std::shared_ptr<BaseCamera> camera)
{
    if (!_manager)
        throw std::logic_error("SolutionDraw: manager is not set");

    _manager->drawSceneWithCamera(scene, _visitor, _drawer, camera);
}
