#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <memory>
#include <vector>

#include "point.h"
#include "edge.h"
#include "object.h"
#include "camera.h"
#include "scene.h"

#include "skeleton_model.h"
#include "list_model_structure.h"

#include "qt_drawer.h"
#include "drawer_visitor.h"

#include "transform_manager.h"
#include "draw_manager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto *qscene = new QGraphicsScene(0, 0, 800, 600);
    auto *view = new QGraphicsView(qscene);

    view->resize(800, 600);
    view->show();

    std::vector<Point> points = {
        Point(-80, -80,  80),
        Point( 80, -80,  80),
        Point( 80,  80,  80),
        Point(-80,  80,  80),

        Point(-80, -80, -80),
        Point( 80, -80, -80),
        Point( 80,  80, -80),
        Point(-80,  80, -80)
    };

    std::vector<Edge> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    auto structure = std::make_shared<ListModelStructure>(points, edges);

    auto cube = std::make_shared<SkeletonModel>(structure);

    Point move(0, 0, 100);
    Point scale(1, 1, 1);
    Point rotate(0, 45, 0);

    TransformManager::transformObject(cube, move, scale, rotate);

    TransformManager::rotateObject(cube, 45, 0, 0);

    auto scene = std::make_shared<Scene>();
    scene->addObject(cube);

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(Point(0, 0, -200));

    TransformManager::moveObject(camera, 0, 0, 0);
    TransformManager::rotateObject(camera, 0, 0, 0);

    auto drawer = std::make_shared<QtDrawer>(qscene);
    auto visitor = DrawerVisitor::instance(drawer, camera);

    DrawManager::instance()->setVisitor(visitor);

    drawer->clearScene();
    DrawManager::instance()->drawScene(scene);

    return app.exec();
}
