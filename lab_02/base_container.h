#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include <cstddef>

class BaseContainer
{
public:
    virtual bool isEmpty() const;
    virtual size_t getSize() const;
    virtual ~BaseContainer();

protected:
    size_t size = 0;
};

#endif
