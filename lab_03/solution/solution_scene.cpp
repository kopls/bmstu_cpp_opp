#include "solution_scene.h"

#include <stdexcept>

SolutionScene::SolutionScene(std::shared_ptr<SceneManager> manager)
    : _manager(manager)
{
}

void SolutionScene::setScene(std::shared_ptr<Scene> scene)
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    _manager->setScene(scene);
}

std::shared_ptr<Scene> SolutionScene::getScene() const
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    return _manager->getScene();
}

void SolutionScene::addObjectWithId(const std::shared_ptr<Object> &object, const std::shared_ptr<std::size_t> &id)
{
    auto scene = getScene();

    if (!scene)
        throw std::logic_error("SolutionScene: scene is not set");

    scene->addObjectWithId(object, id);
}

void SolutionScene::deleteObject(std::size_t id)
{
    auto scene = getScene();

    if (!scene)
        throw std::logic_error("SolutionScene: scene is not set");

    scene->deleteObject(id);
}

void SolutionScene::collectVisibleObjectsToComposite()
{
    auto scene = getScene();

    if (!scene)
        throw std::logic_error("SolutionScene: scene is not set");

    scene->collectVisibleObjectsToComposite();
}

void SolutionScene::splitCompositesToObjects()
{
    auto scene = getScene();

    if (!scene)
        throw std::logic_error("SolutionScene: scene is not set");

    scene->splitCompositesToObjects();
}

void SolutionScene::setCamera(std::size_t id)
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    _manager->setCamera(id);
}

std::shared_ptr<BaseCamera> SolutionScene::getCamera() const
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    return _manager->getCamera();
}

std::size_t SolutionScene::getCameraId() const
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    return _manager->getCameraId();
}

bool SolutionScene::hasCamera() const
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    return _manager->hasCamera();
}

std::vector<std::size_t> SolutionScene::getCameraIds() const
{
    auto scene = getScene();

    if (!scene)
        return {};

    return scene->getCameraIds();
}

SceneMemento SolutionScene::createMemento() const
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    return _manager->createMemento();
}

void SolutionScene::restoreMemento(const SceneMemento &memento)
{
    if (!_manager)
        throw std::logic_error("SolutionScene: manager is not set");

    _manager->restoreMemento(memento);
}
