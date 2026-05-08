#ifndef DRAW_MANAGER_CREATOR_H
#define DRAW_MANAGER_CREATOR_H

#include <memory>

#include "base_manager_creator.h"
#include "draw_manager.h"

class DrawManagerCreator : public BaseManagerCreator<DrawManager>
{
protected:
    std::shared_ptr<DrawManager> create() override
    {
        return std::make_shared<DrawManager>();
    }
};

#endif
