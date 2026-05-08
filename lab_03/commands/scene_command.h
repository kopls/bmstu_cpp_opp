#ifndef COMMANDS_SCENE_COMMAND_H
#define COMMANDS_SCENE_COMMAND_H

#include <cstddef>
#include <memory>
#include <string>

#include "base_command.h"
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
    using Action = void (DrawManager::*)(std::shared_ptr<Scene>);

public:
    DrawScene();
    void execute() override;

private:
    Action method;
};

class LoadScene : public SceneCommand
{
    using Action = std::shared_ptr<Scene> (LoadManager::*)(const std::string &);

public:
    explicit LoadScene(std::string fileName);
    void execute() override;

private:
    Action method;
    std::string fileName;
};

class LoadModel : public SceneCommand
{
    using Action = std::shared_ptr<Object> (LoadManager::*)(const std::string &);

public:
    explicit LoadModel(std::string fileName, ID id = nullptr);
    void execute() override;

private:
    Action method;
    std::string fileName;
    ID id;
};

#endif
