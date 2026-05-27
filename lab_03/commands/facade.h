#ifndef COMMANDS_FACADE_H
#define COMMANDS_FACADE_H

#include <memory>

#include "base_command.h"
#include "solution_pack.h"

class Facade
{
public:
    Facade() = default;
    explicit Facade(const CommandProxy &proxy);
    explicit Facade(const SolutionPack &solutions);

    void setProxy(const CommandProxy &proxy);
    void setSolutions(const SolutionPack &solutions);
    CommandProxy getProxy() const;

    void execute(BaseCommand &command);
    void execute(const std::shared_ptr<BaseCommand> &command);

private:
    CommandProxy proxy;
};

#endif
