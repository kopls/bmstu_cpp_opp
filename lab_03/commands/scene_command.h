#ifndef COMMANDS_SCENE_COMMAND_H
#define COMMANDS_SCENE_COMMAND_H

#include <cstddef>
#include <memory>
#include <string>

#include "base_command.h"
#include "base_camera.h"
#include "model_load_options.h"
#include "object.h"
#include "scene.h"
#include "solution_draw.h"
#include "solution_load.h"
#include "solution_scene.h"

class SceneCommand : public BaseCommand
{
public:
    ~SceneCommand() override = default;
};

class DrawScene : public SceneCommand
{
    using Action = void (SolutionDraw::*)(std::shared_ptr<Scene>, std::shared_ptr<BaseCamera>);

public:
    DrawScene();
    void execute() override;

private:
    Action method;
};

class LoadScene : public SceneCommand
{
    using Action = std::shared_ptr<Scene> (SolutionLoad::*)(const std::string &);

public:
    explicit LoadScene(std::string fileName);
    void execute() override;

private:
    Action method;
    std::string fileName;
};

class LoadModel : public SceneCommand
{
    using Action = void (SolutionLoad::*)(const std::shared_ptr<Scene> &, const std::string &, const std::shared_ptr<std::size_t> &);

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
    using Action = void (SolutionLoad::*)(const std::shared_ptr<Scene> &,
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
    using Action = void (SolutionScene::*)();

public:
    CollectModelsToComposite();
    void execute() override;

private:
    Action method;
};

class SplitCompositeToModels : public SceneCommand
{
    using Action = void (SolutionScene::*)();

public:
    SplitCompositeToModels();
    void execute() override;

private:
    Action method;
};

#endif
