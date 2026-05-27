#include "qt_drawer.h"

QtDrawer::QtDrawer(QGraphicsScene *scene, QGraphicsView *view)
    : _scene(scene), _view(view)
{
}

QtDrawer::QtDrawer(QtDrawer &drawer)
{
    _scene = drawer._scene;
    _view = drawer._view;
}

void QtDrawer::drawLine(const Point &p1, const Point &p2)
{
    _scene->addLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void QtDrawer::clearScene()
{
    _scene->clear();
}

double QtDrawer::getWidth() const
{
    if (_view)
    {
        const double width = _view->contentsRect().width();
        if (width > 0.0)
            return width;
    }

    if (_scene)
    {
        const double width = _scene->sceneRect().width();
        if (width > 0.0)
            return width;
    }

    return 1.0;
}

double QtDrawer::getHeight() const
{
    if (_view)
    {
        const double height = _view->contentsRect().height();
        if (height > 0.0)
            return height;
    }

    if (_scene)
    {
        const double height = _scene->sceneRect().height();
        if (height > 0.0)
            return height;
    }

    return 1.0;
}
