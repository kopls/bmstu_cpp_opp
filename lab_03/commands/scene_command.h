#ifndef SCENE_COMMAND_H
#define SCENE_COMMAND_H

#include <cstddef>
#include <memory>
#include <string>

#include "commands/base_command.h"
#include "base_drawer.h"
#include "base_visitor.h"
#include "draw_manager.h"
#include "load_manager.h"
#include "object.h"
#include "scene.h"
#include "scene_manager.h"

class SceneCommand : public BaseCommand
{
public:
    ~SceneCommand() override = default;
};

class DrawScene : public SceneCommand
{
public:
    using Action = void (DrawManager::*)(std::shared_ptr<Scene>);

    DrawScene(std::shared_ptr<DrawManager> drawManager,
              std::shared_ptr<SceneManager> sceneManager,
              std::shared_ptr<BaseVisitor> visitor,
              std::shared_ptr<BaseDrawer> drawer,
              Action action = &DrawManager::drawScene);

    void execute() override;

private:
    std::shared_ptr<DrawManager> _receiver;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<BaseVisitor> _visitor;
    std::shared_ptr<BaseDrawer> _drawer;
    Action _action;
};

class LoadScene : public SceneCommand
{
public:
    using Action = std::shared_ptr<Scene> (LoadManager::*)(const std::string &);

    LoadScene(std::shared_ptr<LoadManager> loadManager,
              std::shared_ptr<SceneManager> sceneManager,
              std::string fileName,
              Action action = &LoadManager::loadScene);

    void execute() override;

private:
    std::shared_ptr<LoadManager> _receiver;
    std::shared_ptr<SceneManager> _sceneManager;
    Action _action;

    std::string _fileName;
};

class LoadModel : public SceneCommand
{
public:
    using Action = std::shared_ptr<Object> (LoadManager::*)(const std::string &);

    LoadModel(std::shared_ptr<LoadManager> loadManager,
              std::shared_ptr<SceneManager> sceneManager,
              std::string fileName,
              std::shared_ptr<std::size_t> id = nullptr,
              Action action = &LoadManager::load);

    void execute() override;

private:
    std::shared_ptr<LoadManager> _receiver;
    std::shared_ptr<SceneManager> _sceneManager;
    Action _action;

    std::string _fileName;
    std::shared_ptr<std::size_t> _id;
};

#endif
