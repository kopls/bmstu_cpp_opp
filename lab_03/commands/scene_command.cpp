#include "scene_command.h"

#include <utility>

DrawScene::DrawScene()
    : method(static_cast<Action>(&DrawManager::drawScene))
{
}

void DrawScene::execute()
{
    ((*(proxy.draw)).*method)(currentScene(), proxy.drawVisitor, proxy.drawer, proxy.scene->getCamera());
}

LoadScene::LoadScene(std::string fileName)
    : method(&LoadManager::loadScene), fileName(std::move(fileName))
{
}

void LoadScene::execute()
{
    proxy.scene->setScene(((*(proxy.load)).*method)(fileName));
}

LoadModel::LoadModel(std::string fileName, ID id)
    : method(static_cast<Action>(&LoadManager::load)), fileName(std::move(fileName)), id(id)
{
}

void LoadModel::execute()
{
    ((*(proxy.load)).*method)(currentScene(), fileName, id);
}
