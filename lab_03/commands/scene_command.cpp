#include "scene_command.h"

#include <utility>

DrawScene::DrawScene()
    : method(&SolutionDraw::drawSceneWithCamera)
{
}

void DrawScene::execute()
{
    ((*(proxy.draw)).*method)(currentScene(), proxy.scene->getCamera());
}

LoadScene::LoadScene(std::string fileName)
    : method(&SolutionLoad::loadScene), fileName(std::move(fileName))
{
}

void LoadScene::execute()
{
    proxy.scene->setScene(((*(proxy.load)).*method)(fileName));
}

LoadModel::LoadModel(std::string fileName, ID id)
    : method(&SolutionLoad::loadObjectToScene), fileName(std::move(fileName)), id(id)
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
    : method(&SolutionLoad::loadModelToScene),
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
    : method(&SolutionScene::collectVisibleObjectsToComposite)
{
}

void CollectModelsToComposite::execute()
{
    ((*(proxy.scene)).*method)();
}

SplitCompositeToModels::SplitCompositeToModels()
    : method(&SolutionScene::splitCompositesToObjects)
{
}

void SplitCompositeToModels::execute()
{
    ((*(proxy.scene)).*method)();
}
