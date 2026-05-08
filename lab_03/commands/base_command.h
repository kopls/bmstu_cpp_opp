#ifndef COMMANDS_BASE_COMMAND_H
#define COMMANDS_BASE_COMMAND_H

#include <cstddef>
#include <memory>
#include <stdexcept>

#include "base_drawer.h"
#include "base_visitor.h"
#include "draw_manager.h"
#include "load_manager.h"
#include "scene_manager.h"
#include "transform_manager.h"

using ID = std::shared_ptr<std::size_t>;

struct CommandProxy
{
    std::shared_ptr<SceneManager> scene;
    std::shared_ptr<TransformManager> transform;
    std::shared_ptr<DrawManager> draw;
    std::shared_ptr<LoadManager> load;
    std::shared_ptr<BaseVisitor> drawVisitor;
    std::shared_ptr<BaseDrawer> drawer;
};

class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual void execute() = 0;

    static void setProxy(const CommandProxy &commandProxy);

protected:
    static CommandProxy proxy;

    static std::shared_ptr<Scene> currentScene();
};

#endif
