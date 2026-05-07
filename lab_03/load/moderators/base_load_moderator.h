#ifndef BASE_LOAD_MODERATOR_H
#define BASE_LOAD_MODERATOR_H

#include <memory>
#include <string>

#include "object.h"

class BaseLoadModerator
{
public:
    BaseLoadModerator() = default;
    virtual ~BaseLoadModerator() = default;

    virtual std::shared_ptr<Object> load(const std::string &fileName) = 0;
};

#endif
