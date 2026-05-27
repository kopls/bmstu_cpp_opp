#include "mainwindow.h"

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <stdexcept>
#include <string>

#include "camera.h"
#include "camera_command.h"
#include "camera_impl.h"
#include "model_command.h"
#include "scene_command.h"
#include "qt_factory.h"
#include "solution_draw_creator.h"
#include "solution_load_creator.h"
#include "solution_scene_creator.h"
#include "solution_transform_creator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setupFacade();
    setupConnections();
    setupInitialCamera();
    redraw();

    setFocusPolicy(Qt::StrongFocus);
    _graphicsView->setFocusPolicy(Qt::StrongFocus);
    qApp->installEventFilter(this);
    _graphicsView->viewport()->installEventFilter(this);
    _graphicsView->setMouseTracking(true);
    _graphicsView->viewport()->setMouseTracking(true);
}

void MainWindow::setupUi()
{
    auto *central = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(central);
    auto *panel = new QWidget(central);
    auto *panelLayout = new QVBoxLayout(panel);

    _graphicsScene = new QGraphicsScene(0, 0, 800, 600, this);
    _graphicsView = new QGraphicsView(_graphicsScene, central);
    _graphicsView->setMinimumSize(800, 600);
    _graphicsView->setSceneRect(0, 0, 800, 600);
    _graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    _addCameraButton = new QPushButton("Создать камеру", panel);
    _switchCameraButton = new QPushButton("Переключить камеру", panel);
    _loadModelButton = new QPushButton("Загрузить модель", panel);
    _collectCompositeButton = new QPushButton("Собрать модели в композит", panel);
    _splitCompositeButton = new QPushButton("Разъединить композит", panel);
    _undoButton = new QPushButton("Отменить операцию", panel);

    _cameraBox = new QComboBox(panel);
    _fileFormatBox = new QComboBox(panel);
    _representationBox = new QComboBox(panel);

    _fileFormatBox->addItem("Текстовый файл");
    _fileFormatBox->addItem("Бинарный файл");
    _representationBox->addItem("ListModelStructure");
    _representationBox->addItem("MatrixModelStructure");

    _statusLabel = new QLabel("W/A/S/D — движение относительно взгляда, ЛКМ + мышь — поворот камеры", panel);
    _statusLabel->setWordWrap(true);

    panelLayout->addWidget(new QLabel("Камеры", panel));
    panelLayout->addWidget(_cameraBox);
    panelLayout->addWidget(_addCameraButton);
    panelLayout->addWidget(_switchCameraButton);
    panelLayout->addSpacing(12);
    panelLayout->addWidget(new QLabel("Формат данных модели", panel));
    panelLayout->addWidget(_fileFormatBox);
    panelLayout->addWidget(new QLabel("Представление модели", panel));
    panelLayout->addWidget(_representationBox);
    panelLayout->addWidget(_loadModelButton);
    panelLayout->addSpacing(12);
    panelLayout->addWidget(_collectCompositeButton);
    panelLayout->addWidget(_splitCompositeButton);
    panelLayout->addSpacing(12);
    panelLayout->addWidget(_undoButton);
    panelLayout->addStretch();
    panelLayout->addWidget(_statusLabel);

    mainLayout->addWidget(_graphicsView, 1);
    mainLayout->addWidget(panel);

    setCentralWidget(central);
    resize(1120, 700);
    setWindowTitle("3D Viewer");
}

void MainWindow::setupFacade()
{
    SolutionSceneCreator sceneCreator;
    SolutionTransformCreator transformCreator;
    SolutionLoadCreator loadCreator;

    auto drawerFactory = std::make_shared<QtFactory>(_graphicsScene, _graphicsView);
    SolutionDrawCreator drawCreator(drawerFactory);

    _solutions.scene = sceneCreator.getSolution();
    _solutions.transform = transformCreator.getSolution();
    _solutions.load = loadCreator.getSolution();
    _solutions.draw = drawCreator.getSolution();

    _facade = std::make_shared<Facade>(_solutions);
}

void MainWindow::setupConnections()
{
    connect(_addCameraButton, &QPushButton::clicked, this, [this]() { addCameraAtCurrentPosition(); });
    connect(_switchCameraButton, &QPushButton::clicked, this, [this]() { switchCamera(); });
    connect(_loadModelButton, &QPushButton::clicked, this, [this]() { loadModel(); });
    connect(_collectCompositeButton, &QPushButton::clicked, this, [this]() { collectModelsToComposite(); });
    connect(_splitCompositeButton, &QPushButton::clicked, this, [this]() { splitCompositeToModels(); });
    connect(_undoButton, &QPushButton::clicked, this, [this]() { undo(); });

    connect(_cameraBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        if (index >= 0)
            switchCamera();
    });
}

void MainWindow::setupInitialCamera()
{
    auto impl = std::make_shared<CameraImpl>(Point(0, 0, -500));
    auto camera = std::make_shared<Camera>(impl);

    ID id = std::make_shared<std::size_t>();
    AddCamera addCamera(camera, id);
    _facade->execute(addCamera);

    _cameraIds.push_back(*id);
    _cameraBox->addItem("Camera 1");
    _cameraBox->setCurrentIndex(0);
    ++_cameraCounter;

    SetCamera setCamera(*id);
    _facade->execute(setCamera);
}

void MainWindow::addCameraAtCurrentPosition()
{
    try
    {
        saveHistory();

        const Point position = currentCameraPosition();
        auto impl = std::make_shared<CameraImpl>(position);
        auto camera = std::make_shared<Camera>(impl);

        ID id = std::make_shared<std::size_t>();
        AddCamera addCamera(camera, id);
        _facade->execute(addCamera);

        _cameraIds.push_back(*id);
        ++_cameraCounter;
        _cameraBox->addItem(QString("Camera %1").arg(_cameraCounter));
        _cameraBox->setCurrentIndex(_cameraBox->count() - 1);

        SetCamera setCamera(*id);
        _facade->execute(setCamera);
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

void MainWindow::switchCamera()
{
    try
    {
        if (_cameraBox->currentIndex() < 0 || _cameraIds.empty())
            return;

        SetCamera setCamera(selectedCameraId());
        _facade->execute(setCamera);
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

ModelFileFormat MainWindow::selectedFileFormat() const
{
    if (_fileFormatBox->currentIndex() == 1)
        return ModelFileFormat::Binary;

    return ModelFileFormat::Text;
}

ModelRepresentation MainWindow::selectedRepresentation() const
{
    if (_representationBox->currentIndex() == 1)
        return ModelRepresentation::Matrix;

    return ModelRepresentation::List;
}

void MainWindow::loadModel()
{
    try
    {
        const QString filter = selectedFileFormat() == ModelFileFormat::Binary
                                   ? "Binary files (*.bin);;All files (*)"
                                   : "Text files (*.txt);;All files (*)";
        const QString modelsDir = QDir::current().absoluteFilePath("models");
        const QString startDir = QDir(modelsDir).exists() ? modelsDir : QString();
        const QString fileName = QFileDialog::getOpenFileName(this, "Загрузка модели", startDir, filter);
        if (fileName.isEmpty())
            return;

        saveHistory();

        ID id = std::make_shared<std::size_t>();
        LoadModelWithOptions loadModel(fileName.toStdString(), selectedFileFormat(), selectedRepresentation(), id);
        _facade->execute(loadModel);

        _modelIds.push_back(*id);
        ++_modelCounter;
        _statusLabel->setText(QString("Загружено моделей: %1").arg(_modelCounter));
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

void MainWindow::collectModelsToComposite()
{
    try
    {
        saveHistory();

        CollectModelsToComposite command;
        _facade->execute(command);
        _statusLabel->setText("Все видимые модели собраны в композит");
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

void MainWindow::splitCompositeToModels()
{
    try
    {
        saveHistory();

        SplitCompositeToModels command;
        _facade->execute(command);
        _statusLabel->setText("Композиты разъединены в объекты");
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

void MainWindow::saveHistory()
{
    if (!_solutions.scene)
        return;

    _history.push_back(_solutions.scene->createMemento());

    if (_history.size() > 50)
        _history.erase(_history.begin());
}

void MainWindow::undo()
{
    try
    {
        if (_history.empty())
        {
            _statusLabel->setText("История операций пуста");
            return;
        }

        const SceneMemento memento = _history.back();
        _history.pop_back();

        _solutions.scene->restoreMemento(memento);
        refreshCameraBox();
        _statusLabel->setText("Операция отменена");
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

void MainWindow::refreshCameraBox()
{
    if (!_solutions.scene || !_solutions.scene->getScene())
        return;

    const std::size_t activeId = _solutions.scene->getCameraId();
    _cameraIds = _solutions.scene->getCameraIds();

    _cameraBox->blockSignals(true);
    _cameraBox->clear();

    int activeIndex = 0;
    int index = 0;

    for (const auto id : _cameraIds)
    {
        _cameraBox->addItem(QString("Camera %1").arg(index + 1));
        if (id == activeId)
            activeIndex = index;
        ++index;
    }

    if (!_cameraIds.empty())
        _cameraBox->setCurrentIndex(activeIndex);

    _cameraBox->blockSignals(false);
}

void MainWindow::moveActiveCamera(double dx, double dy, double dz)
{
    try
    {
        if (_cameraIds.empty())
            return;

        saveHistory();

        MoveCamera moveCamera(selectedCameraId(), dx, dy, dz);
        _facade->execute(moveCamera);
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

void MainWindow::moveActiveCameraByBasis(double forwardStep, double rightStep, double upStep)
{
    auto camera = currentCamera();

    if (!camera)
        return;

    const Point &forward = camera->getForward();
    const Point &right = camera->getRight();
    const Point &up = camera->getUp();

    const double dx = forward.getX() * forwardStep + right.getX() * rightStep + up.getX() * upStep;
    const double dy = forward.getY() * forwardStep + right.getY() * rightStep + up.getY() * upStep;
    const double dz = forward.getZ() * forwardStep + right.getZ() * rightStep + up.getZ() * upStep;

    moveActiveCamera(dx, dy, dz);
}

void MainWindow::rotateActiveCamera(double ox, double oy, double oz)
{
    try
    {
        if (_cameraIds.empty())
            return;

        saveHistory();

        RotateCamera rotateCamera(selectedCameraId(), ox, oy, oz);
        _facade->execute(rotateCamera);
        redraw();
    }
    catch (const std::exception &error)
    {
        showError(QString::fromStdString(error.what()));
    }
}

void MainWindow::redraw()
{
    DrawScene drawScene;
    _facade->execute(drawScene);
}

std::shared_ptr<BaseCamera> MainWindow::currentCamera() const
{
    std::shared_ptr<BaseCamera> camera;
    GetCamera getCamera(camera);
    _facade->execute(getCamera);

    return camera;
}

Point MainWindow::currentCameraPosition() const
{
    auto camera = currentCamera();

    if (!camera)
        return Point(0, 0, -500);

    return camera->getLocation();
}

std::size_t MainWindow::selectedCameraId() const
{
    const int index = _cameraBox->currentIndex();
    if (index < 0 || static_cast<std::size_t>(index) >= _cameraIds.size())
        throw std::logic_error("Camera is not selected");

    return _cameraIds[static_cast<std::size_t>(index)];
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        moveActiveCameraByBasis(_cameraStep, 0, 0);
        break;
    case Qt::Key_S:
        moveActiveCameraByBasis(-_cameraStep, 0, 0);
        break;
    case Qt::Key_A:
        moveActiveCameraByBasis(0, -_cameraStep, 0);
        break;
    case Qt::Key_D:
        moveActiveCameraByBasis(0, _cameraStep, 0);
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto *keyEvent = static_cast<QKeyEvent *>(event);
        switch (keyEvent->key())
        {
        case Qt::Key_W:
        case Qt::Key_S:
        case Qt::Key_A:
        case Qt::Key_D:
            keyPressEvent(keyEvent);
            return true;
        default:
            break;
        }
    }

    if (object == _graphicsView->viewport())
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            auto *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)
            {
                _mouseRotating = true;
                _lastMousePos = mouseEvent->pos();
                return true;
            }
        }

        if (event->type() == QEvent::MouseMove && _mouseRotating)
        {
            auto *mouseEvent = static_cast<QMouseEvent *>(event);
            const QPoint delta = mouseEvent->pos() - _lastMousePos;
            _lastMousePos = mouseEvent->pos();

            rotateActiveCamera(delta.y() * _mouseSensitivity,
                               delta.x() * _mouseSensitivity,
                               0);
            return true;
        }

        if (event->type() == QEvent::MouseButtonRelease)
        {
            auto *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton)
            {
                _mouseRotating = false;
                return true;
            }
        }
    }

    return QMainWindow::eventFilter(object, event);
}
