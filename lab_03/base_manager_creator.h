#ifndef BASE_MANAGER_CREATOR_H
#define BASE_MANAGER_CREATOR_H

class BaseManagerCreator
{
public:
    virtual ~BaseManagerCreator() = default;
    virtual createManager() = 0;
}

#endif
