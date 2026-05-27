#ifndef COMMANDS_BASE_COMMAND_H
#define COMMANDS_BASE_COMMAND_H

#include <cstddef>
#include <memory>
#include <stdexcept>

#include "scene.h"
#include "solution_draw.h"
#include "solution_load.h"
#include "solution_scene.h"
#include "solution_transform.h"

using ID = std::shared_ptr<std::size_t>;

struct CommandProxy
{
    std::shared_ptr<SolutionScene> scene;
    std::shared_ptr<SolutionTransform> transform;
    std::shared_ptr<SolutionDraw> draw;
    std::shared_ptr<SolutionLoad> load;
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
