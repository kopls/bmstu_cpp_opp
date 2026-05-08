#include "scene_command.h"

#include <stdexcept>
#include <utility>

#include "drawer_visitor.h"

DrawScene::DrawScene()
    : method(&DrawManager::drawScene)
{
}

void DrawScene::execute()
{
    if (!proxy.draw)
        throw std::logic_error("DrawScene: draw manager is not set");

    auto scene = currentScene();

    auto drawerVisitor = std::dynamic_pointer_cast<DrawerVisitor>(proxy.drawVisitor);
    if (!drawerVisitor)
        throw std::logic_error("DrawScene: draw visitor is not set");

    drawerVisitor->setDrawer(proxy.drawer);
    drawerVisitor->setCamera(proxy.scene->getCamera());

    if (proxy.drawer)
        proxy.drawer->clearScene();

    proxy.draw->setVisitor(proxy.drawVisitor);
    ((*(proxy.draw)).*method)(scene);
}

LoadScene::LoadScene(std::string fileName)
    : method(&LoadManager::loadScene), fileName(std::move(fileName))
{
}

void LoadScene::execute()
{
    if (!proxy.load || !proxy.scene)
        throw std::logic_error("LoadScene: managers are not set");

    auto scene = ((*(proxy.load)).*method)(fileName);
    proxy.scene->setScene(scene);
}

LoadModel::LoadModel(std::string fileName, ID id)
    : method(&LoadManager::load), fileName(std::move(fileName)), id(id)
{
}

void LoadModel::execute()
{
    if (!proxy.load)
        throw std::logic_error("LoadModel: load manager is not set");

    auto scene = currentScene();
    auto object = ((*(proxy.load)).*method)(fileName);

    scene->addObject(object);

    if (id)
        *id = object->getId();
}
