#ifndef QT_FACTORY_H
#define QT_FACTORY_H

#include <memory>

#include "base_drawer_factory.h"
#include "qt_drawer.h"

class QtFactory : public BaseDrawerFactory
{
public:
    explicit QtFactory(QGraphicsScene *scene) : _scene(scene) {}

    std::unique_ptr<BaseDrawer> createDrawer() override
    {
        return std::make_unique<QtDrawer>(_scene);
    }

private:
    QGraphicsScene *_scene;
};

#endif
