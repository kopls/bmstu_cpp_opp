#ifndef QT_FACTORY_H
#define QT_FACTORY_H

#include <memory>

#include "base_drawer_factory.h"

class QtFactory : public BaseDrawerFactory
{
public:
     std::unique_ptr<BaseDrawer> createDrawer() override
     {
         return std::make_unique<QtDrawer>;
     }
};

#endif
