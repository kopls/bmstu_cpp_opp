#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>

#include <cstddef>
#include <memory>
#include <vector>

#include "base_camera.h"
#include "base_drawer.h"
#include "base_visitor.h"
#include "draw_manager.h"
#include "facade.h"
#include "load_manager.h"
#include "point.h"
#include "scene_manager.h"
#include "transform_manager.h"

class QComboBox;
class QGraphicsScene;
class QGraphicsView;
class QLabel;
class QPushButton;
class QWidget;
class QObject;
class QEvent;
class QKeyEvent;

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    void setupUi();
    void setupFacade();
    void setupInitialCamera();
    void setupConnections();

    void addCameraAtCurrentPosition();
    void switchCamera();
    void loadModel();

    void moveActiveCamera(double dx, double dy, double dz);
    void moveActiveCameraByBasis(double forwardStep, double rightStep, double upStep);
    void rotateActiveCamera(double ox, double oy, double oz);
    void redraw();

    std::shared_ptr<BaseCamera> currentCamera() const;
    Point currentCameraPosition() const;
    std::size_t selectedCameraId() const;
    void showError(const QString &message);

private:
    QGraphicsScene *_graphicsScene{nullptr};
    QGraphicsView *_graphicsView{nullptr};
    QPushButton *_addCameraButton{nullptr};
    QPushButton *_switchCameraButton{nullptr};
    QPushButton *_loadModelButton{nullptr};
    QComboBox *_cameraBox{nullptr};
    QLabel *_statusLabel{nullptr};

    std::shared_ptr<Facade> _facade;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _transformManager;
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<LoadManager> _loadManager;
    std::shared_ptr<BaseVisitor> _drawVisitor;
    std::shared_ptr<BaseDrawer> _drawer;

    std::vector<std::size_t> _cameraIds;
    std::vector<std::size_t> _modelIds;
    std::size_t _cameraCounter{0};
    std::size_t _modelCounter{0};
    double _cameraStep{25.0};
    double _mouseSensitivity{0.2};
    bool _mouseRotating{false};
    QPoint _lastMousePos;
};

#endif
