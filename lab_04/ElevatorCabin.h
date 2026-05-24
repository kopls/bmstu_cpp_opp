#pragma once

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "ElevatorDoors.h"

#define CABINE_MOVING_BETWEEN_FLOORS_TIME 4000

class ElevatorCabin final : public QObject
{
    Q_OBJECT

    enum CabinStatus {
        MOVING_BETWEEN_FLOORS,
        STOPPING_ON_FLOOR,
        PASSING_FLOOR,
        READY_TO_MOVE
    };

signals:
    void openDoorsSignal();
    void cabinePassedFloorSignal(bool wasInterrupted, int floor);
    void cabineReadyToMoveSignal();

public:
    explicit ElevatorCabin(QObject* parent = nullptr);
    ~ElevatorCabin() = default;

public slots:
    void moveBetweenFloorsSlot(int newCurFloor);
    void stopOnFloorSlot();

    void passFloorSlot();
    void readyToMoveSlot();

private:
    ElevatorDoors doors;
    CabinStatus status;
    QTimer moveTimer;
    int curFloor;
};
