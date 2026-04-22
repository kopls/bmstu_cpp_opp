#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>

#include "skeleton_model.h"
#include "list_model_structure.h"
#include "drawer_visitor.h"
#include "qt_drawer.h"
#include "draw_manager.h"
#include "scene_manager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGraphicsScene *qscene = new QGraphicsScene(-50, -50, 400, 300);
    QGraphicsView *view = new QGraphicsView(qscene);

    view->setWindowTitle("Lab 03 - Skeleton Model");
    view->resize(400, 300);
    view->show();

    std::vector<Point> points = {
        {100, 100, 0},  
        {200, 100, 0},  
        {200, 200, 0},  
        {100, 200, 0},  
    };
    std::vector<Edge> edges = {
        {0, 1}, 
        {1, 2}, 
        {2, 3}, 
        {3, 0}, 
    };


    auto structure = std::make_shared<ListModelStructure>(points, edges);
    auto model = std::make_shared<SkeletonModel>(structure);

    auto scene = std::make_shared<Scene>();
    scene->addObject(model);


    auto drawManager = DrawManager::instance();
    auto sceneManager = SceneManager::instance();

    auto drawer = std::make_shared<QtDrawer>(qscene);
    auto drawerVisitor = DrawerVisitor::instance(drawer);

    sceneManager->setScene(scene);
    drawManager->setVisitor(drawerVisitor);

    drawManager->drawScene(scene);

    return app.exec();
}
