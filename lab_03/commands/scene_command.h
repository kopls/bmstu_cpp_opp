#ifndef COMMANDS_SCENE_COMMAND_H
#define COMMANDS_SCENE_COMMAND_H

#include <cstddef>
#include <memory>
#include <string>

#include "base_command.h"
#include "base_camera.h"
#include "base_drawer.h"
#include "base_visitor.h"
#include "draw_manager.h"
#include "load_manager.h"
#include "model_load_options.h"
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
    using Action = void (DrawManager::*)(std::shared_ptr<Scene>,
                                         std::shared_ptr<BaseVisitor>,
                                         std::shared_ptr<BaseDrawer>,
                                         std::shared_ptr<BaseCamera>);

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
    using Action = void (LoadManager::*)(const std::shared_ptr<Scene> &, const std::string &, const std::shared_ptr<std::size_t> &);

public:
    explicit LoadModel(std::string fileName, ID id = nullptr);
    void execute() override;

private:
    Action method;
    std::string fileName;
    ID id;
};

class LoadModelWithOptions : public SceneCommand
{
    using Action = void (LoadManager::*)(const std::shared_ptr<Scene> &,
                                         const std::string &,
                                         ModelFileFormat,
                                         ModelRepresentation,
                                         const std::shared_ptr<std::size_t> &);

public:
    LoadModelWithOptions(std::string fileName,
                         ModelFileFormat format,
                         ModelRepresentation representation,
                         ID id = nullptr);
    void execute() override;

private:
    Action method;
    std::string fileName;
    ModelFileFormat format;
    ModelRepresentation representation;
    ID id;
};

class CollectModelsToComposite : public SceneCommand
{
    using Action = void (Scene::*)();

public:
    CollectModelsToComposite();
    void execute() override;

private:
    Action method;
};

class SplitCompositeToModels : public SceneCommand
{
    using Action = void (Scene::*)();

public:
    SplitCompositeToModels();
    void execute() override;

private:
    Action method;
};

#endif
