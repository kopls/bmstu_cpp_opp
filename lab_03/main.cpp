#include <iostream>
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

    std::vector<Point> points1 = {{100, 100, 0}, {150, 100, 0}, {150, 150, 0}, {100, 150, 0}};
    std::vector<Edge> edges1 = {{0,1}, {1,2}, {2,3}, {3,0}};
    auto structure1 = std::make_shared<ListModelStructure>(points1, edges1);
    auto model1 = std::make_shared<SkeletonModel>(structure1);
    
    std::vector<Point> points2 = {{200, 100, 0}, {250, 100, 0}, {250, 150, 0}, {200, 150, 0}};
    std::vector<Edge> edges2 = {{0,1}, {1,2}, {2,3}, {3,0}};
    auto structure2 = std::make_shared<ListModelStructure>(points2, edges2);
    auto model2 = std::make_shared<SkeletonModel>(structure2);
    
    std::vector<Point> points3 = {{150, 200, 0}, {200, 200, 0}, {200, 250, 0}, {150, 250, 0}};
    std::vector<Edge> edges3 = {{0,1}, {1,2}, {2,3}, {3,0}};
    auto structure3 = std::make_shared<ListModelStructure>(points3, edges3);
    auto model3 = std::make_shared<SkeletonModel>(structure3);

    auto composite = std::make_shared<Composite>();
    composite->add(model1);
    composite->add(model2);
    composite->add(model3);

    auto scene = std::make_shared<Scene>();
    scene->addObject(composite);

     std::cout << "Composite size before removal: " << std::distance(composite->begin(), composite->end()) << std::endl;

    // Находим и удаляем model2 из композита
    for (auto it = composite->begin(); it != composite->end(); ++it) {
        if (*it == model2) {
            composite->remove(it);
            std::cout << "Model2 removed from composite" << std::endl;
            break;
        }
    }

    std::cout << "Composite size after removal: " << std::distance(composite->begin(), composite->end()) << std::endl;

    // 5. Создаём ещё один композит и вкладываем его
    auto innerComposite = std::make_shared<Composite>();

    std::vector<Point> points4 = {{50, 50, 0}, {80, 50, 0}, {80, 80, 0}, {50, 80, 0}};
    std::vector<Edge> edges4 = {{0,1}, {1,2}, {2,3}, {3,0}};
    auto structure4 = std::make_shared<ListModelStructure>(points4, edges4);
    auto model4 = std::make_shared<SkeletonModel>(structure4);

    innerComposite->add(model4);
    composite->add(innerComposite);  // вкладываем композит в композит!

    std::cout << "Inner composite added" << std::endl;

    auto drawManager = DrawManager::instance();
    auto sceneManager = SceneManager::instance();

    auto drawer = std::make_shared<QtDrawer>(qscene);
    auto drawerVisitor = DrawerVisitor::instance(drawer);

    sceneManager->setScene(scene);
    drawManager->setVisitor(drawerVisitor);

    drawManager->drawScene(scene);

    return app.exec();
}
