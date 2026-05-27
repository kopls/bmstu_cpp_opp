#ifndef QT_FACTORY_H
#define QT_FACTORY_H

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "base_drawer_factory.h"
#include "qt_drawer.h"

class QtFactory : public BaseDrawerFactory
{
public:
    QtFactory(QGraphicsScene *scene, QGraphicsView *view)
        : _scene(scene), _view(view)
    {
    }

    std::shared_ptr<BaseDrawer> createDrawer() override
    {
        return std::make_shared<QtDrawer>(_scene, _view);
    }

private:
    QGraphicsScene *_scene;
    QGraphicsView *_view;
};

#endif
