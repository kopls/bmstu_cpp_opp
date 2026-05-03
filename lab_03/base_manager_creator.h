#ifndef BASE_MANAGER_CREATOR_H
#define BASE_MANAGER_CREATOR_H

#include <memory>
#include "base_manager"

class BaseManagerCreator
{
public:
    virtual ~BaseManagerCreator() = default;

    std::shared_ptr<BaseManager> getManager();

protected:
    virtual std::shared_ptr<BaseManager> create() = 0;

private:
    std::shared_ptr<BaseManager> manager{ nullptr };
};

#endif
