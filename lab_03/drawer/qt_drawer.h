#ifndef QT_DRAWER_H
#define QT_DRAWER_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include "base_drawer.h"
#include "point.h"

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;
    QtDrawer(QGraphicsScene *scene, QGraphicsView *view);
    QtDrawer(QtDrawer &drawer);

    void drawLine(const Point &p1, const Point &p2) override;
    void clearScene() override;
    double getWidth() const override;
    double getHeight() const override;

private:
    QGraphicsScene *_scene;
    QGraphicsView *_view;
};

#endif
