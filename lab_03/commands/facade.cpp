#include "facade.h"

#include <stdexcept>

Facade::Facade(const CommandProxy &proxy)
    : proxy(proxy)
{
    BaseCommand::setProxy(this->proxy);
}

void Facade::setProxy(const CommandProxy &proxy)
{
    this->proxy = proxy;
    BaseCommand::setProxy(this->proxy);
}

CommandProxy Facade::getProxy() const
{
    return proxy;
}

void Facade::execute(BaseCommand &command)
{
    BaseCommand::setProxy(proxy);
    command.execute();
}

void Facade::execute(const std::shared_ptr<BaseCommand> &command)
{
    if (!command)
        throw std::logic_error("Facade: command is null");

    execute(*command);
}
