#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QVector>
#include <QPushButton>
#include <QLabel>

#include "Elevator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class CallType {
    CarCall,
    UpCall,
    DownCall
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFloorIndicator(int floor);
    void onFloorButtonClicked(int floor);  

private:
    void setupUI();
    void setupConnections();

    Ui::MainWindow *ui;
    
    // Панель индикаторов текущего этажа
    QVector<QLabel*> m_floorIndicators;
    
    // Кнопки в кабине (9 штук)
    QVector<QPushButton*> m_cabinButtons;
    
    Elevator m_elevator;
};

#endif
