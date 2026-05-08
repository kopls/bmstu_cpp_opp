#ifndef COMMANDS_FACADE_H
#define COMMANDS_FACADE_H

#include <memory>

#include "base_command.h"

class Facade
{
public:
    Facade() = default;
    explicit Facade(const CommandProxy &proxy);

    void setProxy(const CommandProxy &proxy);
    CommandProxy getProxy() const;

    void execute(BaseCommand &command);
    void execute(const std::shared_ptr<BaseCommand> &command);

private:
    CommandProxy proxy;
};

#endif
