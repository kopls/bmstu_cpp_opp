#include "scene_command.h"

#include <utility>

DrawScene::DrawScene()
    : method(&DrawManager::drawSceneWithCamera)
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
    : method(&LoadManager::loadObjectToScene), fileName(std::move(fileName)), id(id)
{
}

void LoadModel::execute()
{
    ((*(proxy.load)).*method)(currentScene(), fileName, id);
}

LoadModelWithOptions::LoadModelWithOptions(std::string fileName,
                                           ModelFileFormat format,
                                           ModelRepresentation representation,
                                           ID id)
    : method(&LoadManager::loadModelToScene),
      fileName(std::move(fileName)),
      format(format),
      representation(representation),
      id(id)
{
}

void LoadModelWithOptions::execute()
{
    ((*(proxy.load)).*method)(currentScene(), fileName, format, representation, id);
}

CollectModelsToComposite::CollectModelsToComposite()
    : method(&Scene::collectVisibleObjectsToComposite)
{
}

void CollectModelsToComposite::execute()
{
    ((*currentScene()).*method)();
}

SplitCompositeToModels::SplitCompositeToModels()
    : method(&Scene::splitCompositesToObjects)
{
}

void SplitCompositeToModels::execute()
{
    ((*currentScene()).*method)();
}
