#pragma once

#include <QObject>
#include <QDebug>
#include "ElevatorCabin.h"
#include "ElevatorController.h"

class Elevator final : public QObject
{
    Q_OBJECT

signals:
    void getNewFloorSignal(int newFloor);
    void throwCurFloorSignal(int curFloor);

public:
    explicit Elevator(QObject* parent = nullptr);
    ~Elevator() = default;

public slots:
    void newFloorSlot(int newFloor);
    void throwFloorToInterfaceSlot(bool wasInterruptedNotNeed, int curFloor);

private:
    ElevatorController controller;
    ElevatorCabin cabine;
};
