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


        // ============================================
    // ТЕСТ 1: Разные Z-координаты (проверка перспективы)
    // ============================================
    std::cout << "\n=== TEST 1: Different Z coordinates ===" << std::endl;

    // Модель близко к камере (Z = 50)
    std::vector<Point> nearPoints = {{-50, -50, 50}, {50, -50, 50}, {50, 50, 50}, {-50, 50, 50}};
    std::vector<Edge> nearEdges = {{0,1}, {1,2}, {2,3}, {3,0}};
    auto nearStructure = std::make_shared<ListModelStructure>(nearPoints, nearEdges);
    auto nearModel = std::make_shared<SkeletonModel>(nearStructure);

    // Модель далеко от камеры (Z = 300)
    std::vector<Point> farPoints = {{-50, -50, 300}, {50, -50, 300}, {50, 50, 300}, {-50, 50, 300}};
    std::vector<Edge> farEdges = {{0,1}, {1,2}, {2,3}, {3,0}};
    auto farStructure = std::make_shared<ListModelStructure>(farPoints, farEdges);
    auto farModel = std::make_shared<SkeletonModel>(farStructure);

    auto depthScene = std::make_shared<Scene>();
    depthScene->addObject(nearModel);
    depthScene->addObject(farModel);

    sceneManager->setScene(depthScene);
    drawManager->drawScene(depthScene);
    std::cout << "Near model (Z=50) and Far model (Z=300) drawn - far should be smaller!" << std::endl;

    // ============================================
    // ТЕСТ 2: Движение камеры
    // ============================================
    std::cout << "\n=== TEST 2: Camera movement ===" << std::endl;

    // Создаём камеру
    auto camera = std::make_shared<Camera>(Point(0, 0, 100));
    camera->focalLength = 500.0;

    auto cameraVisitor = DrawerVisitor::instance(drawer, camera);
    drawManager->setVisitor(cameraVisitor);

    // Сцена с одним объектом в центре
    std::vector<Point> centerPoints = {{-50, -50, 0}, {50, -50, 0}, {50, 50, 0}, {-50, 50, 0}};
    std::vector<Edge> centerEdges = {{0,1}, {1,2}, {2,3}, {3,0}};
    auto centerStructure = std::make_shared<ListModelStructure>(centerPoints, centerEdges);
    auto centerModel = std::make_shared<SkeletonModel>(centerStructure);

    auto cameraScene = std::make_shared<Scene>();
    cameraScene->addObject(centerModel);

    sceneManager->setScene(cameraScene);
    drawManager->drawScene(cameraScene);
    std::cout << "Camera at (0,0,100) - square at center" << std::endl;

    // Двигаем камеру вправо
    camera->location = Point(100, 0, 100);
    drawManager->drawScene(cameraScene);
    std::cout << "Camera moved to (100,0,100) - square should shift left" << std::endl;

    // Двигаем камеру вверх
    camera->location = Point(0, 100, 100);
    drawManager->drawScene(cameraScene);
    std::cout << "Camera moved to (0,100,100) - square should shift down" << std::endl;

    // Приближаем камеру
    camera->location = Point(0, 0, 50);
    drawManager->drawScene(cameraScene);
    std::cout << "Camera zoomed to (0,0,50) - square should be larger!" << std::endl;

    // Отдаляем камеру
    camera->location = Point(0, 0, 300);
    drawManager->drawScene(cameraScene);
    std::cout << "Camera zoomed out to (0,0,300) - square should be smaller!" << std::endl;

    // ============================================
    // ТЕСТ 3: Поворот камеры (если реализован)
    // ============================================
    std::cout << "\n=== TEST 3: Camera rotation ===" << std::endl;

    // Возвращаем камеру в центр
    camera->location = Point(0, 0, 100);

    // Поворачиваем камеру вправо (смотрим вдоль X)
    camera->right = Point(0, 0, -1);
    camera->forward = Point(1, 0, 0);
    drawManager->drawScene(cameraScene);
    std::cout << "Camera rotated right - square should be on the left" << std::endl;

    // Поворачиваем камеру вверх
    camera->right = Point(1, 0, 0);
    camera->up = Point(0, 0, -1);
    camera->forward = Point(0, 1, 0);
    drawManager->drawScene(cameraScene);
    std::cout << "Camera rotated up - square should be at bottom" << std::endl;

    // Сброс камеры
    camera->right = Point(1, 0, 0);
    camera->up = Point(0, 1, 0);
    camera->forward = Point(0, 0, 1);

    // ============================================
    // ТЕСТ 4: Разные фокусные расстояния
    // ============================================
    std::cout << "\n=== TEST 4: Different focal lengths ===" << std::endl;

    camera->location = Point(0, 0, 100);
    camera->focalLength = 250.0;  // широкий угол
    drawManager->drawScene(cameraScene);
    std::cout << "Focal length 250 - wide angle" << std::endl;

    camera->focalLength = 1000.0;  // телеобъектив
    drawManager->drawScene(cameraScene);
    std::cout << "Focal length 1000 - telephoto (zoomed)" << std::endl;

    camera->focalLength = 500.0;  // стандарт

    // ============================================
    // ТЕСТ 5: Исходная сцена (композит)
    // ============================================
    std::cout << "\n=== TEST 5: Original composite scene ===" << std::endl;

    camera->location = Point(0, 0, 200);
    sceneManager->setScene(scene);
    drawManager->drawScene(scene);
    std::cout << "Original composite scene with camera at (0,0,200)" << std::endl;


    return app.exec();
}
