#include "base_container.h"

bool BaseVector::isEmpty() const
{
    return !bool(size);
}

size_t BaseVector::getSize() const
{
    return size;
}

BaseVector::~BaseVector() = default;
