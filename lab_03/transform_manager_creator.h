#ifndef TRANSFORM_MANAGER_CREATOR_H
#define TRANSFORM_MANAGER_CREATOR_H

#include <memory>

#include "base_manager_creator.h"
#include "transform_manager.h"

class TransformManagerCreator : public BaseManagerCreator
{
protected:
    std::shared_ptr<BaseManager> create() override
    {
        return std::make_shared<TransformManager>();
    }
};

#endif
