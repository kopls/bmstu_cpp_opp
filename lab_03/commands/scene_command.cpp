#include "commands/scene_command.h"

#include <stdexcept>

#include "drawer_visitor.h"

DrawScene::DrawScene(std::shared_ptr<DrawManager> drawManager,
                     std::shared_ptr<SceneManager> sceneManager,
                     std::shared_ptr<BaseVisitor> visitor,
                     std::shared_ptr<BaseDrawer> drawer,
                     Action action)
    : _receiver(drawManager),
      _sceneManager(sceneManager),
      _visitor(visitor),
      _drawer(drawer),
      _action(action)
{
}

void DrawScene::execute()
{
    if (!_receiver || !_sceneManager || !_sceneManager->getScene())
        throw std::logic_error("DrawScene: draw manager or scene is not set");

    auto drawerVisitor = std::dynamic_pointer_cast<DrawerVisitor>(_visitor);

    if (!drawerVisitor)
        throw std::logic_error("DrawScene: visitor is not DrawerVisitor");

    drawerVisitor->setDrawer(_drawer);
    drawerVisitor->setCamera(_sceneManager->getCamera());

    if (_drawer)
        _drawer->clearScene();

    _receiver->setVisitor(_visitor);
    ((*_receiver).*_action)(_sceneManager->getScene());
}

LoadScene::LoadScene(std::shared_ptr<LoadManager> loadManager,
                     std::shared_ptr<SceneManager> sceneManager,
                     std::string fileName,
                     Action action)
    : _receiver(loadManager),
      _sceneManager(sceneManager),
      _action(action),
      _fileName(std::move(fileName))
{
}

void LoadScene::execute()
{
    if (!_receiver || !_sceneManager)
        throw std::logic_error("LoadScene: managers are not set");

    auto scene = ((*_receiver).*_action)(_fileName);
    _sceneManager->setScene(scene);
}

LoadModel::LoadModel(std::shared_ptr<LoadManager> loadManager,
                     std::shared_ptr<SceneManager> sceneManager,
                     std::string fileName,
                     std::shared_ptr<std::size_t> id,
                     Action action)
    : _receiver(loadManager),
      _sceneManager(sceneManager),
      _action(action),
      _fileName(std::move(fileName)),
      _id(id)
{
}

void LoadModel::execute()
{
    if (!_receiver || !_sceneManager || !_sceneManager->getScene())
        throw std::logic_error("LoadModel: managers or scene are not set");

    auto object = ((*_receiver).*_action)(_fileName);
    _sceneManager->getScene()->addObject(object);

    if (_id)
        *_id = object->getId();
}
