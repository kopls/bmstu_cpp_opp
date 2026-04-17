#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include <cstddef>

class BaseVector
{
public:
    virtual bool isEmpty() const;
    virtual size_t getSize() const;
    virtual ~BaseVector() = 0;

protected:
    size_t size = 0;
};

#endif
