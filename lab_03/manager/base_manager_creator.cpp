#include "base_manager_creator.h"

#include <memory>

BaseManagerCreator::std::shared_ptr<BaseManager> getManager()
{
    if (!manager)
    {
        manager = create();
    }

    return manager;
}
