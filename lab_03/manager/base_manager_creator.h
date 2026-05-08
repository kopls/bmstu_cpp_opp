#ifndef BASE_MANAGER_CREATOR_H
#define BASE_MANAGER_CREATOR_H

#include <memory>
#include "base_manager"

template <typename Manager>
class BaseManagerCreator
{
public:
    std::shared_ptr<Manager> getManager()
    {
        if (!_manager)
            _manager = create();

        return _manager;
    }

protected:
    virtual std::shared_ptr<Manager> create() = 0;

private:
    std::shared_ptr<Manager> _manager;
};

#endif
