#include "scene_command.h"

DrawScene::DrawScene(std::shared_ptr<BaseDrawer> drawer) : _drawer(drawer) { }

void DrawScene::execute()
{
    _visitor->setDrawer(_drawer);
    _drawManager->drawScene(_sceneManager->getScene());
}


LoadScene::LoadScene(std::string fileName) : _fileName(fileName) { }

void LoadScene::execute()
{

}
