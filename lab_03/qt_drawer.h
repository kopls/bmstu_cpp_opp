#ifndef QT_DRAWER_H
#define QT_DRAWER_H

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;
    explicit QtDrawer(QGraphicsScene *scene);
    QtDrawer(QtDrawer &drawer);

    void drawLine(const Point &p1, const Point &p2) override;
    void clearScene() override;

private:
    QGraphicsScene *_scene;
};

#endif
