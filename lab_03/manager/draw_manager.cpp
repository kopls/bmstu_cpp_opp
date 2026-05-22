#include <memory>
#include <stdexcept>

#include "draw_manager.h"
#include "drawer_visitor.h"

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
    auto drawerVisitor = std::dynamic_pointer_cast<DrawerVisitor>(visitor);
    if (!drawerVisitor)
        throw std::logic_error("DrawManager: draw visitor is not set");

    drawerVisitor->setDrawer(drawer);
    drawerVisitor->setCamera(camera);

    if (drawer)
        drawer->clearScene();

    setVisitor(visitor);
    drawScene(scene);
}
