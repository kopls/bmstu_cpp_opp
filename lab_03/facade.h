#ifndef FACADE_H
#define FACADE_H

#include "base_command"

class Facade
{
public:
    void execute(BaseCommand &command);
}

#endif
