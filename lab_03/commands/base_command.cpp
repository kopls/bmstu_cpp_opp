#include "base_command.h"

CommandProxy BaseCommand::proxy{};

void BaseCommand::setProxy(const CommandProxy &commandProxy)
{
    proxy = commandProxy;
}

std::shared_ptr<Scene> BaseCommand::currentScene()
{
    if (!proxy.scene || !proxy.scene->getScene())
        throw std::logic_error("Command: scene is not set");

    return proxy.scene->getScene();
}
