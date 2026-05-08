#include "qt_drawer.h"

QtDrawer::QtDrawer(QGraphicsScene *scene)
{
    _scene = scene;
}

QtDrawer::QtDrawer(QtDrawer &drawer)
{
    _scene = drawer._scene;
}

void QtDrawer::drawLine(const Point &p1, const Point &p2) 
{
    _scene->addLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void QtDrawer::clearScene()
{
    _scene->clear();
}
