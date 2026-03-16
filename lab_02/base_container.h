#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

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
