#include <memory>
#include <stdexcept>

#include "draw_manager.h"

void DrawManager::drawScene(std::shared_ptr<Scene> scene)
{
    if (!scene)
        throw std::logic_error("DrawManager: scene is not set");

    if (!_visitor)
        throw std::logic_error("DrawManager: visitor is not set");

    for (auto iter = scene->begin(); iter != scene->end(); ++iter)
        (*iter)->accept(*_visitor);
}

void DrawManager::drawScene(std::shared_ptr<Scene> scene,
                            std::shared_ptr<BaseVisitor> visitor,
                            std::shared_ptr<BaseDrawer> drawer,
                            std::shared_ptr<BaseCamera> camera)
{
    if (!visitor)
        throw std::logic_error("DrawManager: draw visitor is not set");

    visitor->setDrawer(drawer);
    visitor->setCamera(camera);

    if (drawer)
        drawer->clearScene();

    setVisitor(visitor);
    drawScene(scene);
}

void DrawManager::drawSceneWithCamera(std::shared_ptr<Scene> scene,
                                      std::shared_ptr<BaseVisitor> visitor,
                                      std::shared_ptr<BaseDrawer> drawer,
                                      std::shared_ptr<BaseCamera> camera)
{
    drawScene(scene, visitor, drawer, camera);
}
