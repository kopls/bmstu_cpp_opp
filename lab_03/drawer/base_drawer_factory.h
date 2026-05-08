#ifndef BASE_DRAWER_FACTORY_H
#define BASE_DRAWER_FACTORY_H

#include <memory>

#include "base_drawer.h"

class BaseDrawerFactory
{
public:
    virtual ~BaseDrawerFactory() = default;
    virtual std::unique_ptr<BaseDrawer> createDrawer() = 0;
};

#endif
