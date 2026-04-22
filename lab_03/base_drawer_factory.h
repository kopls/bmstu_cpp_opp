#ifndef BASE_DRAWER_FACTORY_H
#define BASE_DRAWER_FACTORY_H

class BaseDrawerFactory
{
public:
    virtual ~BaseDrawerFactory() = default;
    virtual std::unique_ptr<BaseDrawer> createDrawer() = 0;
}

#endif
