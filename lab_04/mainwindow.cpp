#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

constexpr int kTotalFloors = 9;
constexpr int kInitialFloor = 1;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(350, 600);
    setWindowTitle("Панель управления");
    
    setupUI();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Центральный виджет
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    
    // Индикатор текущего этажа
    QLabel* titleLabel = new QLabel("", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font: bold 14px; padding: 5px;");
    mainLayout->addWidget(titleLabel);
    
    // Большой индикатор текущего этажа
    QLabel* currentFloorDisplay = new QLabel(QString::number(kInitialFloor), this);
    currentFloorDisplay->setAlignment(Qt::AlignCenter);
    currentFloorDisplay->setStyleSheet(
        "font: bold 48px;"
        "background-color: #2c3e50;"
        "color: #ecf0f1;"
        "border-radius: 20px;"
        "padding: 20px;"
    );
    mainLayout->addWidget(currentFloorDisplay);
    
    // Сохраняем индикатор для обновления
    m_floorIndicators.resize(kTotalFloors + 1);
    m_floorIndicators[kInitialFloor] = currentFloorDisplay;
    
    // ========== ЦЕНТРАЛЬНАЯ ПАНЕЛЬ: Кнопки в кабине ==========
    QLabel* cabinLabel = new QLabel("ЛИФТ", this);
    cabinLabel->setAlignment(Qt::AlignCenter);
    cabinLabel->setStyleSheet("font: bold 16px; padding: 10px; background-color: #34495e; color: white; border-radius: 5px;");
    mainLayout->addWidget(cabinLabel);
    
    // Сетка кнопок 3x3
    QGridLayout* cabinGrid = new QGridLayout();
    cabinGrid->setSpacing(5);
    
    m_cabinButtons.resize(kTotalFloors + 1);
    for (int i = 1; i <= kTotalFloors; ++i)
    {
        int row = (kTotalFloors - i) / 3;
        int col = (kTotalFloors - i) % 3;
        
        QPushButton* btn = new QPushButton(QString::number(i), this);
        btn->setFixedSize(60, 60);
        btn->setStyleSheet(
            "QPushButton {"
            "  background-color: #2c3e50;"
            "  color: white;"
            "  border: none;"
            "  border-radius: 30px;"
            "  font: bold 16px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #34495e;"
            "}"
        );
        
        m_cabinButtons[i] = btn;
        cabinGrid->addWidget(btn, row, col);
    }
    mainLayout->addLayout(cabinGrid);
    
    // ========== НИЖНЯЯ ПАНЕЛЬ: Индикаторы всех этажей ==========
    QLabel* floorsLabel = new QLabel("", this);
    floorsLabel->setAlignment(Qt::AlignCenter);
    floorsLabel->setStyleSheet("font: bold 14px; padding: 5px; margin-top: 10px;");
    mainLayout->addWidget(floorsLabel);
    
    QHBoxLayout* floorsLayout = new QHBoxLayout();
    for (int i = 1; i <= kTotalFloors; ++i)
    {
        QLabel* floorIndicator = new QLabel(QString::number(i), this);
        floorIndicator->setFixedSize(35, 35);
        floorIndicator->setAlignment(Qt::AlignCenter);
        
        if (i == kInitialFloor)
        {
            floorIndicator->setStyleSheet(
                "background-color: #e74c3c;"
                "color: white;"
                "border-radius: 17px;"
                "font: bold 12px;"
            );
        }
        else
        {
            floorIndicator->setStyleSheet(
                "background-color: #7f8c8d;"
                "color: white;"
                "border-radius: 17px;"
                "font: bold 12px;"
            );
        }
        
        floorsLayout->addWidget(floorIndicator);
        m_floorIndicators[i] = floorIndicator;
    }
    mainLayout->addLayout(floorsLayout);
    
    setCentralWidget(central);
}

void MainWindow::setupConnections()
{
    // Подключаем сигнал текущего этажа от лифта к индикаторам
    connect(&m_elevator, &Elevator::throwCurFloorSignal,
            this, &MainWindow::updateFloorIndicator);
    
    // Подключаем кнопки кабины к слоту лифта
    for (int i = 1; i <= kTotalFloors; ++i)
    {
        connect(m_cabinButtons[i], &QPushButton::clicked,
                this, [this, i]() { onFloorButtonClicked(i); });
    }
}

void MainWindow::updateFloorIndicator(int floor)
{
    // Обновляем нижние индикаторы
    for (int i = 1; i <= kTotalFloors; ++i)
    {
        if (i == floor)
        {
            m_floorIndicators[i]->setStyleSheet(
                "background-color: #e74c3c;"
                "color: white;"
                "border-radius: 17px;"
                "font: bold 12px;"
            );
        }
        else
        {
            m_floorIndicators[i]->setStyleSheet(
                "background-color: #7f8c8d;"
                "color: white;"
                "border-radius: 17px;"
                "font: bold 12px;"
            );
        }
    }
    
    // Обновляем большой индикатор
    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel* label : labels)
    {
        if (label->styleSheet().contains("font: bold 48px"))
        {
            label->setText(QString::number(floor));
            break;
        }
    }
    
    // Сбрасываем цвет кнопки в кабине для прибывшего этажа
    if (floor >= 1 && floor <= kTotalFloors && m_cabinButtons[floor])
    {
        m_cabinButtons[floor]->setStyleSheet(
            "QPushButton {"
            "  background-color: #2c3e50;"
            "  color: white;"
            "  border: none;"
            "  border-radius: 30px;"
            "  font: bold 16px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #34495e;"
            "}"
        );
    }
}

void MainWindow::onFloorButtonClicked(int floor)
{
    // Меняем цвет нажатой кнопки на красный
    if (m_cabinButtons[floor])
    {
        m_cabinButtons[floor]->setStyleSheet(
            "QPushButton {"
            "  background-color: #e74c3c;"
            "  color: white;"
            "  border: none;"
            "  border-radius: 30px;"
            "  font: bold 16px;"
            "}"
        );
    }
    
    // Вызываем слот лифта
    m_elevator.newFloorSlot(floor);
}
